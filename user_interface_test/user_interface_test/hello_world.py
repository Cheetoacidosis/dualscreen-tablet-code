import spidev
import time
import os
import sys
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
spi.writebytes([0x0F, 0x07, 0x17, 0x3A, 0x3A, 0x03]) #default settings, but with B/W flipped
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




#run the user interface offscreen
#since we're on terminal OS and
#we're going to send the display
#to the e-ink screen
os.environ["QT_QPA_PLATFORM"] = "offscreen"

from PyQt5.QtWidgets import QApplication
from PyQt5.QtGui import QImage, QPainter, QColor, QFont, QTransform
from PyQt5.QtCore import Qt

#begin the application
app = QApplication(sys.argv)

#create a canvas on which the application will run
#480 x 800 pixels, rgb format (b/w didn't work for me for some reason)
canvas = QImage(480,800,QImage.Format_RGB32)

#fill the whole canvas with white
canvas.fill(Qt.white)

#initialize a painter object so we can add text
painter = QPainter(canvas)

#set the painter to be black
painter.setBrush(QColor(Qt.black))
painter.setPen(QColor(Qt.black))
#painter.drawRect(50,50,200,100)

#set font settings and draw the text at (50,200)
painter.setFont(QFont("Arial", 40))
painter.drawText(50,200,"Hello World!")
painter.end()

#By default, the e-ink screen takes 800 x 480, not 480 x 800 so we need to rotate it
rotated_canvas = canvas.transformed(QTransform().rotate(90))

#now convert to black & white (still don't know why setting it like this initially doesn't work)
mono_canvas = rotated_canvas.convertToFormat(QImage.Format_Mono)

#pull the raw bytes out of the canvas
image_as_bytes = mono_canvas.bits().asstring(48000)
#put the bytes in a list
image_as_byte_list = list(image_as_bytes)

app.quit()

#Write old data
cs_dev.on()
cd_dev.off()
spi.writebytes([0x10]) #write old cmd
cd_dev.on()
for _ in range(12):  
    spi.writebytes([0x01]*4000)
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

#write the canvas bytes to the screen, in 4000 byte chunks (caps out at 4096)
for i in range(0,len(image_as_byte_list), 4000):
    spi.writebytes(image_as_byte_list[i:i+4000])
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
