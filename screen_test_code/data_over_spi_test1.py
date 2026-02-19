import spidev
import time
from gpiozero import Device, DigitalOutputDevice

spi = spidev.SpiDev(0, 1) # create spi object connecting to /dev/spidev0.1
spi.max_speed_hz = 250000 # set speed to 250 Khz

cd_pin = 12 # Command / Data pin
cs_pin = 25 # Chip select pin

cd_dev = DigitalOutputDevice(pin=cd_pin, active_high=True)
cs_dev = DigitalOutputDevice(pin=cs_pin, active_high=False, initial_value=False)

# do the thing

# CS Low (cs_dev.on())
# CD LOW
# send "power on"
# send "the command for a buncha ones"
# CD HIGH
# send "buncha ones"
# CD LOW 
# send "data stop"
# send "refresh"
# CS High (cd_dev.off())


# Hopefully, set the screen to be black

cs_dev.on() 
cd_dev.off()

# Send power on
spi.writebytes([0x04])

# Send Display Start Transmission 1
spi.writebytes([0x10])

# Send our bits
cd_dev.on()
# 24000 bytes, half the screen
for x in range(24000):
    spi.writebytes([0xFF])
    
for x in range(24000):
    spi.writebytes([0x00])
    
# We're done with data, send data stop and refresh
cd_dev.off()
spi.writebytes([0x11]) # data stop
time.sleep(0.01)
spi.writebytes([0x12]) # refresh

cs_dev.off()
