# I2C library
import smbus3
from gpiozero import Device, DigitalOutputDevice, InputDevice, Button
import time
import os

# GT911 I2C address
ADDR = 0x14
# ADDR = 0x5d

COMMAND_REG = [0x80, 0x40]
COMMAND_CHECK_REG = [0x80, 0x46]

# Initialize I2C 
i2c = smbus3.SMBus(1)

# Pins for Interrupt and Reset
int_pin = 18
rst_pin = 26

# Create digital output devices for the touch panel
rst_l_dev = DigitalOutputDevice(pin=rst_pin, initial_value=True)
    # "off" causes the chip to get reset
int_dev = Button(pin=int_pin)

# make sure the device is on
rst_l_dev.on()
time.sleep(0.05)

# Prepare the i2c read / write transactions
STATUS_1B_REG = smbus3.i2c_msg.write(ADDR, [0x81, 0x4E])
CLEAR_STATUS_REG = smbus3.i2c_msg.write(ADDR, [0x81, 0x4E, 0x00])
PRODUCT_INFO_4B_REG = smbus3.i2c_msg.write(ADDR, [0x81, 0x40]) 
TOUCH_XY_REG = smbus3.i2c_msg.write(ADDR, [0x81, 0x4F])

BUFF_1_BYTE = smbus3.i2c_msg.read(ADDR, 1) 
BUFF_4_BYTE = smbus3.i2c_msg.read(ADDR, 4) 

# Validate that the device turned on, and is accessible
i2c.i2c_rdwr(PRODUCT_INFO_4B_REG, BUFF_4_BYTE)
if ("911" not in BUFF_4_BYTE.__str__()):
    raise ConnectionRefusedError("The device attached to I2C address " + str(hex(ADDR)) + " was not a GT911 touch panel, or could not be read")

while(1):
    os.system('cls' if os.name == 'nt' else 'clear')
    print("Touch the screen")

    # Wait for the interrupt (INT) pin to go high
        # THIS DOES NOT ACTUALLY SET UP AN INTERRUPT! The underlying hardware is just polling. There is no way to set up an interrupt in userspace
    int_dev.wait_for_press()
    
    # Read the status register, and break the byte into its component bits
    i2c.i2c_rdwr(STATUS_1B_REG, BUFF_1_BYTE)
    status_response = int.from_bytes(BUFF_1_BYTE.__bytes__())
    ready_to_read = (status_response >> 7) & 0b1
    num_touch = status_response & 0b00000111
    large_touch = (status_response >> 6) & 0b1

    # Read the coordinate registers 
    if ((ready_to_read == 1) & (num_touch != 0)):
        print("Number of touches detected: " + str(num_touch) + (", Large area detected" if large_touch == 1 else ""))

        BUFF_TOUCH = smbus3.i2c_msg.read(ADDR, 8*num_touch)
        i2c.i2c_rdwr(TOUCH_XY_REG, BUFF_TOUCH)

        track_ids = []
        x_coords = []
        y_coords = []
        sizes = []

        # Store the coordinates
        for i in range(0, num_touch):
            track_ids.append(BUFF_TOUCH.__bytes__()[0 + 8*i])
            x_coords.append(int.from_bytes([BUFF_TOUCH.__bytes__()[2 + 8*i], BUFF_TOUCH.__bytes__()[1 + 8*i]]))
            y_coords.append(int.from_bytes([BUFF_TOUCH.__bytes__()[4 + 8*i], BUFF_TOUCH.__bytes__()[3 + 8*i]]))
            sizes.append(int.from_bytes([BUFF_TOUCH.__bytes__()[6 + 8*i], BUFF_TOUCH.__bytes__()[5 + 8*i]]))

            print("Touch " + str(track_ids[i]) + ": (" + str(x_coords[i]) + ", " + str(y_coords[i]) + ") Size: " + str(sizes[i]))

    # CRITICAL! Clear the status register as an ACK
    i2c.i2c_rdwr(CLEAR_STATUS_REG)

    time.sleep(0.005)