import smbus3
# from multiprocessing import Process
from gpiozero import Device, DigitalOutputDevice, InputDevice, Button
# import partial
import time

rst_l_pin = 26
int_pin = 18

rst_l_dev = DigitalOutputDevice(pin=self.rst_pin, initial_value=False)
int_dev = Button(pin=self.int_pin, pull_up = self.pull_up, active_state = self.active_state, hold_time = self.hold_time, hold_repeat = self.hold_repeat, bounce_time = self.bounce_time)
