import spidev
import time
import os
import sys
from gpiozero import Device, DigitalOutputDevice, InputDevice

spi = spidev.SpiDev(0, 1) # create spi object connecting to /dev/spidev0.1
spi.max_speed_hz = 2000000 # set speed to 500 Khz
spi.mode = 0

cd_pin = 12 # Command / Data pin
cs_pin = 25 # Chip select pin
busy_pin = 21 # Busy pin
rst_pin = 16 # Reset pin

cd_dev = DigitalOutputDevice(pin=cd_pin, active_high=True)
cs_dev = DigitalOutputDevice(pin=cs_pin, active_high=False, initial_value=False)
busy_dev = InputDevice(pin=busy_pin, pull_up=False)
rst_dev = DigitalOutputDevice(pin=rst_pin, initial_value=True)



def wait_for_busy():
    time.sleep(0.01)
    while busy_dev.value == 0:
        time.sleep(0.001)

def send_cmd(cmd, data):
    cs_dev.on()
    cd_dev.off()
    spi.writebytes([cmd])
    cd_dev.on()
    spi.writebytes(data)
    cs_dev.off()

def power_on():
    cs_dev.on()
    cd_dev.off()
    spi.writebytes([0x04]) #Power on cmd
    cs_dev.off()
    wait_for_busy()

def write_old_data(data):
    cs_dev.on()
    cd_dev.off()
    spi.writebytes([0x10]) #write old cmd
    cd_dev.on()

    #write the bytes to the screen, in 4000 byte chunks (caps out at 4096)
    for i in range(0,len(data), 4000):
        spi.writebytes(data[i:i+4000])
    cs_dev.off()
    wait_for_busy()

def write_new_data(data):
    cs_dev.on()
    cd_dev.off()
    spi.writebytes([0x13]) #write new cmd
    cd_dev.on()
    wait_for_busy()

    #write the bytes to the screen, in 4000 byte chunks (caps out at 4096)
    for i in range(0,len(data), 4000):
        spi.writebytes(data[i:i+4000])
    cs_dev.off()


def screen_refresh():
    cs_dev.on()
    cd_dev.off()
    spi.writebytes([0x12]) #display refresh cmd
    cs_dev.off()
    wait_for_busy()


def initialize_eink():

    rst_dev.off()
    time.sleep(0.3)
    rst_dev.on()
    time.sleep(0.3)

    #Set panel settings
    #default panel settings, but in B/W mode
    send_cmd(0x00, [0x1F])


    #Set default power settings
    send_cmd(0x01, [0x0F, 0x07, 0x17, 0x3A, 0x3A, 0x03])

    #Set screen resolution 800 x 480
    #800=0x0320, 480=0x01E0
    send_cmd(0x61,[0x03, 0x20, 0x01, 0xE0])

    #Power ON
    power_on()

    #now let's configure the partial refresh LUTs

    #set VCOM LUT
    #ground VCOM - all 0's
    send_cmd(0x20, [0x00]*42)

    #set white-to-white LUT
    #if a pixel was previously white, and it's going to 
    #stay as white, we don't do anything to it - write all
    #zeros.
    send_cmd(0x21, [0x00]*42)

    #set black-to-white LUT
    cs_dev.on()
    cd_dev.off()
    spi.writebytes([0x22])
    cd_dev.on()
    #if a pixel was previously black, we need to set it 
    #to white.

    #0x80 = 0b 10 00 00 00 
    #10 = level 0 set to low voltage (attracts black pigment down, leaving only white)
    #000000 = levels 1,2,3 set to ground
    spi.writebytes([0x80])

    #0x14 = set level 0 voltage for 20 (0x14) frames
    spi.writebytes([0x14])
    #0x00 = set level 1 voltage for 0 frames
    #0x00 = set level 2 voltage for 0 frames
    #0x00 = set level 3 voltage for 0 frames
    spi.writebytes([0x00,0x00,0x00])

    #0x01 = perform phase 1 once
    spi.writebytes([0x01])

    #all following 0x00 = set all the voltages for all the following
    #phases to 0, and do each of those phases 0 times
    spi.writebytes([0x00]*36)
    cs_dev.off()



    #set white-to-black LUT

    cs_dev.on()
    cd_dev.off()
    spi.writebytes([0x23])
    cd_dev.on()
    #if pixel was previously white, we need to set it to black.
    #same as black-to-white, but first byte is 0x40, which sets
    #voltage to high, pushing black pigment up rather than down
    spi.writebytes([0x40, 0x14, 0x00, 0x00, 0x00, 0x01])
    spi.writebytes([0x00]*36)
    cs_dev.off()

    #set black-to-black LUT
    #if a pixel was previously black, and it's going to 
    #stay as black, we don't do anything to it - write all
    #zeros.
    send_cmd(0x24, [0x00]*42)

def switch_to_fast_refresh_mode():
    #Change panel settings
    send_cmd(0x00,[0x3F])
    # default settings, but in B/W mode and REG is set to 
    #read the refresh commands from the LUT that we specify in
    #the LUT registers. This means we can make our own Look Up Table
    #and functionally enable partial refresh


initialize_eink()

#Write old data
write_old_data([0x00]*48000)

#Write new data
write_new_data([0x00]*48000)

#Screen refresh
screen_refresh()

screen_data_file = open("/dev/shm/display_data.bin", "rb")
screen_data = screen_data_file.read()

#Write old data
write_old_data([0x00]*48000)

write_new_data(screen_data)

switch_to_fast_refresh_mode()

screen_refresh()

old_data = screen_data



while True:
    screen_data_file.seek(0)
    new_data = screen_data_file.read()
    if new_data != old_data:
        write_old_data(old_data)
        write_new_data(new_data)
        screen_refresh()
        print("updated screen")
        old_data=new_data

        time.sleep(0.1)








spi.close()
