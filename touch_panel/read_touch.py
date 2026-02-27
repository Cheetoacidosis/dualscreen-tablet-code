# I2C library
import smbus3
from gpiozero import Device, DigitalOutputDevice, InputDevice
import time

#Secondary GT911 I2C address
# ADDR = 0x14
ADDR = 0x5d

COMMAND_REG = [0x80, 0x40]
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
START_COORD_READ = smbus3.i2c_msg.write(ADDR, COMMAND_REG + [0x00])
STATUS_REG = smbus3.i2c_msg.write(ADDR, [0x81, 0x4E])
X_PT1_REG = smbus3.i2c_msg.write(ADDR, [0x81, 0x58])
Y_PT1_REG = smbus3.i2c_msg.write(ADDR, [0x81, 0x5A])
READ_ONE_BYTE = smbus3.i2c_msg.read(ADDR, 1) 
READ_TWO_BYTE = smbus3.i2c_msg.read(ADDR, 2) 


# Put into coord reading mode
i2c.i2c_rdwr(START_COORD_READ)

# for val in range(0, 100):
while(1):
    
    i2c.i2c_rdwr(STATUS_REG, READ_ONE_BYTE)
    for value in READ_ONE_BYTE:
        if (value == 128):
            i2c.i2c_rdwr(X_PT1_REG, READ_TWO_BYTE)
            for val in READ_TWO_BYTE:
                print(val)

    time.sleep(0.001)

