# I2C library
import smbus
from gpiozero import Device, DigitalOutputDevice, InputDevice
import time

#  GT911 reported 7-bit address 0x5d
touch_address = 0x5d

# Initialize I2C (SMBus)
bus = smbus.SMBus(1) #GPIO

int_pin = 18
rst_pin = 26

rst_dev = DigitalOutputDevice(pin=rst_pin, initial_value=True)
int_dev = DigitalOutputDevice(pin=int_pin, initial_value=True)


# Try changing the address of the doodad
rst_dev.off()
int_dev.off()

time.sleep(1)

rst_dev.on()

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