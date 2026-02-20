import spidev
import time
from gpiozero import Device, DigitalOutputDevice, InputDevice

spi = spidev.SpiDev(0, 1) # create spi object connecting to /dev/spidev0.1
spi.max_speed_hz = 500000 # set speed to 500 Khz
spi.mode = 0

cd_pin = 12 # Command / Data pin
cs_pin = 25 # Chip select pin
busy_pin = 21 # Busy pin
rst_pin = 16 # Reset pin

cd_dev = DigitalOutputDevice(pin=cd_pin, active_high=True)
cs_dev = DigitalOutputDevice(pin=cs_pin, active_high=False, initial_value=False)
busy_dev = InputDevice(pin=busy_pin, pull_up=False)
rst_dev = DigitalOutputDevice(pin=rst_pin, initial_value=True)

#Pseudocode
#Set panel settings
#Set default power settings
#Set screen resolution 800 x 480
#Power ON
#Wait for busy
#Write old data
#Wait for busy
#Write new data
#Wait for busy
#Screen refresh



#Reset device (only necessary after power cycle)
#Waiting 0.3 is a bit excessive - 0.2 works, but 0.1 does not
rst_dev.off()
time.sleep(0.3)
rst_dev.on()
time.sleep(0.3)

#Set panel settings
cs_dev.on()
cd_dev.off()
spi.writebytes([0x00]) #set panel settings
cd_dev.on()
spi.writebytes([0x1F]) #default settings, but in B/W mode
cs_dev.off()

#Set default power settings
cs_dev.on()
cd_dev.off()
spi.writebytes([0x01]) #set power settings
cd_dev.on()
spi.writebytes([0x0F, 0x07, 0x17, 0x3A, 0x3A, 0x03]) #default settings
cs_dev.off()

#Set screen resolution 800 x 480
cs_dev.on()
cd_dev.off()
spi.writebytes([0x61]) #screen resolution
cd_dev.on()
spi.writebytes([0x03, 0x20, 0x01, 0xE0]) #800=0x320, 480=0x1E0
cs_dev.off()

#Power ON
cs_dev.on()
cd_dev.off()
spi.writebytes([0x04]) #Power on cmd
cs_dev.off()

#Wait for busy
time.sleep(0.1)
while busy_dev.value == 0:
    time.sleep(0.01)

#Write old data
cs_dev.on()
cd_dev.off()
spi.writebytes([0x10]) #write old cmd
cd_dev.on()
for _ in range(12):  
    spi.writebytes([0xFF]*4000)
cs_dev.off()

#Wait for busy
time.sleep(0.1)
while busy_dev.value == 0:
    time.sleep(0.01)

#Write new data
cs_dev.on()
cd_dev.off()
spi.writebytes([0x13]) #write new cmd
cd_dev.on()
for _ in range(12):  
    spi.writebytes([0x00]*4000)
cs_dev.off()

#Wait for busy
time.sleep(0.1)
while busy_dev.value == 0:
    time.sleep(0.01)

#Screen refresh
cs_dev.on()
cd_dev.off()
spi.writebytes([0x12]) #display refresh cmd
cs_dev.off()

#Wait for busy
time.sleep(0.1)
while busy_dev.value == 0:
    time.sleep(0.01)

spi.close()
