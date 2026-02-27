# I2C library
import smbus3
from gpiozero import Device, DigitalOutputDevice, InputDevice
import time

#Secondary GT911 I2C address
ADDR = 0x14

# Initialize I2C 
i2c = smbus3.SMBus(1)

# Pins for Interrupt and Reset
int_pin = 18
rst_pin = 26

# Create digital output devices for the touch panel
rst_l_dev = DigitalOutputDevice(pin=rst_pin, initial_value=True)
    # "off" causes the chip to get reset
int_dev = DigitalOutputDevice(pin=int_pin, initial_value=True)

# make sure the device is on
rst_l_dev.on()
time.sleep(0.001)

# Prepare the i2c read / write transactions
                    # write() tells the GT911 what register to report from
                                #I2CAddress, [Bytes to Write]
FIRMWARE_REG = smbus3.i2c_msg.write(ADDR, [0x81, 0x44])
                    # read() acts both as the instructions to read, and the buffer where data is stored
                                #I2CAddress, Length of buffer (bytes)
READ_TWO_BYTE = smbus3.i2c_msg.read(ADDR, 2) 

# Read the firmware version, and store the value in READ_TWO_BYTE
i2c.i2c_rdwr(FIRMWARE_REG, READ_TWO_BYTE)

# Iterate through and print out the recieved values
for val in READ_TWO_BYTE:
    print(val)
