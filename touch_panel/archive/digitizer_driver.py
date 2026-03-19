# Driver for GT911
import smbus2
from gpiozero import Device, DigitalOutputDevice, InputDevice
import time

panel0_gpio = [26, 18]
# rst_l = io26  INT = io18 
panel1_gpio = [0,0] 
#not yet defined

address_ind = [0x5d, 0x14]

def switch_address(address_ind):
    """
    Set the address of the specified digitzer panel

    Args
    ~~~~panel_ind - 0-1 index of the panel to change the address of
    address_ind - 0-1 which address you want it changed to
    """
    int_pin = 18
    rst_pin = 26

    rst_l_dev = DigitalOutputDevice(pin=rst_pin, initial_value=True)
        # "off" causes the chip to get reset
    int_dev = DigitalOutputDevice(pin=int_pin, initial_value=True)

    if (address_ind == 0): #0x5d
        int_dev.off()
        rst_l_dev.off() 
        rst_l_dev.on()
    elif(address_ind == 1): #0x14
        int_dev.on()
        rst_l_dev.off() 
        rst_l_dev.on()
