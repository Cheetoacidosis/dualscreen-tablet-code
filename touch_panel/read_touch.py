# I2C library
import smbus3
from gpiozero import Device, DigitalOutputDevice, InputDevice
import time

#Secondary GT911 I2C address
# ADDR = 0x14
ADDR = 0x5d

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
# int_dev = DigitalOutputDevice(pin=int_pin, initial_value=True)

# make sure the device is on
rst_l_dev.on()
time.sleep(0.05)

# Prepare the i2c read / write transactions
STATUS_1B_REG = smbus3.i2c_msg.write(ADDR, [0x81, 0x4E])
CLEAR_STATUS_REG = smbus3.i2c_msg.write(ADDR, [0x81, 0x4E, 0x00])

PRODUCT_INFO_4B_REG = smbus3.i2c_msg.write(ADDR, [0x81, 0x40]) 
START_COORD_READ = smbus3.i2c_msg.write(ADDR, COMMAND_REG + [0x00])
TOUCH_PTS_1B_REG = smbus3.i2c_msg.write(ADDR, [0x80, 0x4C])
X_RES_2B_REG = smbus3.i2c_msg.write(ADDR, [0x80, 0x48])
Y_RES_2B_REG = smbus3.i2c_msg.write(ADDR, [0x80, 0x4A])
READ_X_RES_2B_REG = smbus3.i2c_msg.write(ADDR, [0x81, 0x46])
READ_Y_RES_2B_REG = smbus3.i2c_msg.write(ADDR, [0x81, 0x48])
REFRESH_RATE_1B_REG = smbus3.i2c_msg.write(ADDR, [0x80, 0x56])

X_PT1_REG = smbus3.i2c_msg.write(ADDR, [0x81, 0x58])
Y_PT1_REG = smbus3.i2c_msg.write(ADDR, [0x81, 0x5A])

BUFF_1_BYTE = smbus3.i2c_msg.read(ADDR, 1) 
BUFF_2_BYTE = smbus3.i2c_msg.read(ADDR, 2) 
BUFF_4_BYTE = smbus3.i2c_msg.read(ADDR, 4) 

# Validate that the device turned on, and is accessible
i2c.i2c_rdwr(PRODUCT_INFO_4B_REG, BUFF_4_BYTE)
if ("911" not in BUFF_4_BYTE.__str__()):
    raise ConnectionRefusedError("The device attached to I2C address " + str(hex(ADDR)) + " was not a GT911 touch panel, or could not be read")

# Configure GT911's configuration registers
    """Read:
    # touch points
    x res
    y res
    refresh rate"""

i2c.i2c_rdwr(TOUCH_PTS_1B_REG, BUFF_1_BYTE)
print("Config number of touch points: " + str(BUFF_1_BYTE.__bytes__()))

i2c.i2c_rdwr(STATUS_1B_REG, BUFF_1_BYTE)
print("Status number of touch points (last 3 bits): " + str(BUFF_1_BYTE.__bytes__()))

i2c.i2c_rdwr(X_RES_2B_REG, BUFF_2_BYTE)
print("Config X Resolution: " + str(BUFF_2_BYTE.__bytes__()))

i2c.i2c_rdwr(READ_X_RES_2B_REG, BUFF_2_BYTE)
print("Status X Resolution: " + str(BUFF_2_BYTE.__bytes__()))

i2c.i2c_rdwr(Y_RES_2B_REG, BUFF_2_BYTE)
print("Config Y Resolution: " + str(BUFF_2_BYTE.__bytes__()))

i2c.i2c_rdwr(READ_Y_RES_2B_REG, BUFF_2_BYTE)
print("Status Y Resolution: " + str(BUFF_2_BYTE.__bytes__()))

i2c.i2c_rdwr(REFRESH_RATE_1B_REG, BUFF_1_BYTE)
print("Config refresh rate: " + str(BUFF_1_BYTE.__bytes__()))



while(1):
    
    i2c.i2c_rdwr(STATUS_1B_REG, BUFF_1_BYTE)
    # print("Status register: " + str(BUFF_1_BYTE.__bytes__()))
    # print(BUFF_1_BYTE.__bytes__())
    # print((int(BUFF_1_BYTE.__bytes__())))
    status_response = int.from_bytes(BUFF_1_BYTE.__bytes__())
    ready_to_read = status_response >> 7
    num_touch = status_response & 0b00000111

    if (ready_to_read == 1):
        print("Ready response recieved. " + str(num_touch) + " touches detected. Clearing status register")
        i2c.i2c_rdwr(CLEAR_STATUS_REG)

        # Check if clearing the status register worked properly
        i2c.i2c_rdwr(STATUS_1B_REG, BUFF_1_BYTE)
        status_response = int.from_bytes(BUFF_1_BYTE.__bytes__())
        ready_to_read = status_response >> 7

        if (ready_to_read == 1):
            print("CLEAR UNSUCCESSFUL")
        else:
            print("Clear successful")

    # if ()
    # for value in BUFF_1_BYTE:
    #     if (value == 128):
    #         i2c.i2c_rdwr(X_PT1_REG, BUFF_2_BYTE)
    #         for val in BUFF_2_BYTE:
    #             print(val)

    time.sleep(0.001)