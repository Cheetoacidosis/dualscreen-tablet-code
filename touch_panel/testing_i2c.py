# I2C library
import smbus2
from gpiozero import Device, DigitalOutputDevice, InputDevice
import time

FIRMWARE_REG = 0x8144
TOUCH_NUMBER_REG = 0x804c
COMMAND_STATUS_REG = 0x81A8
COMMAND_CHECK_REG = 0x8046
COMMAND_REG = 0x8040

CONFIG_CHKSUM_REG = 0x80FF
CONFIG_FRESH_REG = 0x8100

COORD_STATUS_REG = 0x814E

ENTER_RECEIVE_MODE = 0x22


#  GT911 reported 7-bit address 0x5d
# 8bit write address 0xBA
# 8bit read address  0xBB
# ADDR = 0x5d
ADDR = 0x5d

# Initialize I2C (SMBus)
i2c = smbus2.SMBus(1)

int_pin = 18
rst_pin = 26

rst_dev = DigitalOutputDevice(pin=rst_pin, initial_value=True)
int_dev = DigitalOutputDevice(pin=int_pin, initial_value=True)


# See if we can make any changes at fucking all
rst_dev.off()
time.sleep(1)

CSR_second = i2c.read_byte_data(ADDR, 0x814e)

print(CSR_second)

# touchnum = i2c.read_byte_data(ADDR, TOUCH_NUMBER_REG)
# print(touchnum)

# firm_low = i2c.read_byte_data(ADDR, FIRMWARE_REG)
# firm_high = i2c.read_byte_data(ADDR, FIRMWARE_REG + 1)

# print(firm_low)
# print(firm_high)

# Try changing the address of the doodad
# rst_dev.off()
# int_dev.off()

# time.sleep(1)

# rst_dev.on()

# rst_dev.off()
# int_dev.on()

# time.sleep(0.0001)

# rst_dev.on()

# time.sleep(0.005)

# int_dev.off()



# Create a sawtooth wave 16 times
# for i in range(0x10000):

#     # Create our 12-bit number representing relative voltage
#     voltage = i & 0xfff

#     # Shift everything left by 4 bits and separate bytes
#     msg = (voltage & 0xff0) >> 4
#     msg = [msg, (msg & 0xf) << 4]

#     # Write out I2C command: address, reg_write_dac, msg[0], msg[1]
#     bus.write_i2c_block_data(address, reg_write_dac, msg)