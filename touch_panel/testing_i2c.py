# I2C library
import smbus3
from gpiozero import Device, DigitalOutputDevice, InputDevice
import time
import ctypes
# from digitizer_driver import switch_address

# FIRMWARE_REG = 0x8144
# TOUCH_NUMBER_REG = 0x804c
# COMMAND_STATUS_REG = 0x81A8
# COMMAND_CHECK_REG = 0x8046
# COMMAND_REG = 0x8040

# CONFIG_CHKSUM_REG = 0x80FF
# CONFIG_FRESH_REG = 0x8100

# COORD_STATUS_REG = 0x814E

# ENTER_RECEIVE_MODE = 0x22


#  GT911 reported 7-bit address 0x5d
# 8bit write address 0xBA
# 8bit read address  0xBB
# ADDR = 0x5d
ADDR = 0x14

# Initialize I2C (SMBus)
i2c = smbus3.SMBus(1)




int_pin = 18
rst_pin = 26

rst_l_dev = DigitalOutputDevice(pin=rst_pin, initial_value=True)
    # "off" causes the chip to get reset
int_dev = DigitalOutputDevice(pin=int_pin, initial_value=True)

# make sure the device is on
rst_l_dev.on()
time.sleep(0.001)

# Create the i2c read / write transactions
                                #I2CAddress, [Bytes to Write]
FIRMWARE_REG = smbus3.i2c_msg.write(ADDR, [0x81, 0x44])
                                #I2CAddress, Length of buffer (bytes)
READ_TWO_BYTE = smbus3.i2c_msg.read(ADDR, 2) 


i2c.i2c_rdwr(FIRMWARE_REG, READ_TWO_BYTE)

for val in READ_TWO_BYTE:
    print(val)
