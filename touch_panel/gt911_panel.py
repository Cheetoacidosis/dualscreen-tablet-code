import smbus3
# from multiprocessing import Process
from gpiozero import Device, DigitalOutputDevice, InputDevice, Button
# import partial
import time
import os

class GT911_Panel:
    COMMAND_REG = [0x80, 0x40]
    COMMAND_CHECK_REG = [0x80, 0x46]
    i2c = smbus3.SMBus(1)
    pull_up = True
    active_state = None
    bounce_time = 4 * 10**(-9)
    hold_time = 4 * 10**(-6)
    hold_repeat = False


    def __init__(self, int_pin, rst_pin, i2c_address):
        if (i2c_address in [0x5d, 0x14]):
            self.ADDR = i2c_address
        else:
            raise ValueError("Invalid I2C address for GT911. Valid addresses are 0x5d or 0x14")

        self.rst_pin = rst_pin
        self.int_pin = int_pin
        self.connected = False
        self.fresh = False
        self.is_reading = False

        self.track_ids = []
        self.x_coords = []
        self.y_coords = []
        self.touch_sizes = []

        self.STATUS_1B_REG = smbus3.i2c_msg.write(self.ADDR, [0x81, 0x4E])
        self.CLEAR_STATUS_REG = smbus3.i2c_msg.write(self.ADDR, [0x81, 0x4E, 0x00])
        self.PRODUCT_INFO_4B_REG = smbus3.i2c_msg.write(self.ADDR, [0x81, 0x40]) 
        self.TOUCH_XY_REG = smbus3.i2c_msg.write(self.ADDR, [0x81, 0x4F])

        self.BUFF_1_BYTE = smbus3.i2c_msg.read(self.ADDR, 1) 
        self.BUFF_4_BYTE = smbus3.i2c_msg.read(self.ADDR, 4) 

        self.rst_l_dev = DigitalOutputDevice(pin=self.rst_pin, initial_value=False)
        self.int_dev = Button(pin=self.int_pin, pull_up = self.pull_up, active_state = self.active_state, hold_time = self.hold_time, hold_repeat = self.hold_repeat, bounce_time = self.bounce_time)


    def connect(self):
        """
        Attempt to connect to the touch panel over i2c

        Returns: True if connection was successful, False if failed
        """
        self.int_dev.close()
        self.rst_l_dev.close()
        self.is_reading = False

        # Create digital output devices for the touch panel controls
        self.rst_l_dev = DigitalOutputDevice(pin=self.rst_pin, initial_value=False)
            # "off" causes the chip to get reset
        int_dev = DigitalOutputDevice(pin=self.int_pin, initial_value=False)

        # Turn the device on, and set I2C address
        if self.ADDR == 0x14:
            # Set address to 0x14
            int_dev.on()
            time.sleep(0.0001)
            self.rst_l_dev.on()
            time.sleep(0.005)
            int_dev.off()
            time.sleep(0.05)
            int_dev.close()
        else:
            # Set address to 0x5d
            int_dev.off()
            time.sleep(0.0001)
            self.rst_l_dev.on()
            time.sleep(0.005)
            int_dev.off()
            time.sleep(0.05)
            int_dev.close()

        # Listen on INT for incoming presses
        self.int_dev = Button(pin=self.int_pin, pull_up = self.pull_up, active_state = self.active_state, hold_time = self.hold_time, hold_repeat = self.hold_repeat, bounce_time = self.bounce_time)
        # Setup i2c writes
        PRODUCT_INFO_4B_REG = smbus3.i2c_msg.write(self.ADDR, [0x81, 0x40]) 
        BUFF_4_BYTE = smbus3.i2c_msg.read(self.ADDR, 4) 

        # Validate that the device turned on, and is accessible
        try: 
            self.i2c.i2c_rdwr(PRODUCT_INFO_4B_REG, BUFF_4_BYTE)
        except OSError:
            self.connected = False
            return False

        if ("911" not in BUFF_4_BYTE.__str__()):
            raise ConnectionRefusedError("The device attached to I2C address " + str(hex(self.ADDR)) + " was not a GT911 touch panel, or could not be read")
        
        self.connected = True
        self.is_reading = False
        return True
        







    def __read_coord_registers(self):

        # Don't try to read if connection was lost
        if self.connected == False:
            print("Returned False from readcoordreg (self.connected == false)")
            self.is_reading = False
            return False
        

        ready_to_read = 0

        # Read the status register & loop until it's valid
        while (ready_to_read == 0):
            # If we err out, try reconnecting with the panel
            try:
                self.i2c.i2c_rdwr(self.STATUS_1B_REG, self.BUFF_1_BYTE)
            except OSError:
                print("Panel disconnected")
                return False

            status_response = int.from_bytes(self.BUFF_1_BYTE.__bytes__())
            ready_to_read = (status_response >> 7) & 0b1
            num_touch = status_response & 0b00000111
            large_touch = (status_response >> 6) & 0b1
            have_key = (status_response >> 4) & 0b1

            # If we don't have data to read, try again in 1ms
            if (ready_to_read == 0):
                time.sleep(0.001)

        # Read the coordinate registers 
        if (num_touch > 0):
        # if ((ready_to_read == 1)):
            # print("Number of touches detected: " + str(num_touch) + (", Large area detected" if large_touch == 1 else ""))

            self.BUFF_TOUCH = smbus3.i2c_msg.read(self.ADDR, 8*num_touch)
            
            try:
                self.i2c.i2c_rdwr(self.TOUCH_XY_REG, self.BUFF_TOUCH)
            except OSError:
                print("Panel disconnected")
                return False

            self.track_ids = []
            self.x_coords = []
            self.y_coords = []
            self.touch_sizes = []

            # Store the coordinates
            for i in range(0, num_touch):
                self.track_ids.append(self.BUFF_TOUCH.__bytes__()[0 + 8*i])
                self.x_coords.append(int.from_bytes([self.BUFF_TOUCH.__bytes__()[2 + 8*i], self.BUFF_TOUCH.__bytes__()[1 + 8*i]]))
                self.y_coords.append(int.from_bytes([self.BUFF_TOUCH.__bytes__()[4 + 8*i], self.BUFF_TOUCH.__bytes__()[3 + 8*i]]))
                self.touch_sizes.append(int.from_bytes([self.BUFF_TOUCH.__bytes__()[6 + 8*i], self.BUFF_TOUCH.__bytes__()[5 + 8*i]]))

                # print("Touch " + str(self.track_ids[i]) + ": (" + str(self.x_coords[i]) + ", " + str(self.y_coords[i]) + ") Size: " + str(self.touch_sizes[i]))
        # Nothing in the coord registers - empty the boys
        else:
            self.track_ids = [None]
            self.x_coords = [None]
            self.y_coords = [None]
            self.touch_sizes = [None]

        # CRITICAL! Clear the status register as an ACK
        try:
            self.i2c.i2c_rdwr(self.CLEAR_STATUS_REG)
        except OSError:
            print("Panel disconnected")
            return False
            
        self.fresh = True
        self.is_reading = False
        return True


    def start_reading(self):
        """
        Essentially sets up an interrupt on INT. In practice it is still polling, 
        but to this level it looks like an interrupt
        """
        self.int_dev.close()
        self.int_dev = Button(pin=self.int_pin, pull_up = self.pull_up, active_state = self.active_state, hold_time = self.hold_time, hold_repeat = self.hold_repeat, bounce_time = self.bounce_time)
        self.int_dev.when_pressed = self.INTpin_ISR
        # self.__read_coord_registers()
        # self.int_dev.when_pressed = self.woag

        # count = 0
        # self.reading_process = Process(target=self.__read_loop)
        # self.reading_process.start()



        #     time.sleep(0.005)
        #     if self.int_dev.is_active:
        #         print("Active ", self.int_dev.held_time)
        #         count += 1

    # def __read_loop(self):
    #     while (True):
    #         if (self.is_reading == False):
    #             self.is_reading = True
    #             self.__read_coord_registers()

    def INTpin_ISR(self):
        # print("ISR Triggered")
        # Skip if a read is already ongoing
        # if (self.is_reading == False):
            self.is_reading = True
            self.__read_coord_registers()
        # else:
            # print("Skipped reading (ISR)")




    def coords(self):
        if (self.connected == False):
            return ([], [])

        self.fresh = False

        retval = dict()
        for idx in range(len(self.track_ids)):
            retval[self.track_ids[idx]] = [self.x_coords[idx], self.y_coords[idx]]

        return retval


    def disconnected(self):
        """
        If the panel disconnects, sever EVERYTHING!!!
        """