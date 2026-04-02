"""
(Untested 3/28)
Should send touch inputs from the GT911 to the linux userspace
"""

import os
import time
from gt911_panel import GT911_Panel
from evdev import UInput, AbsInfo, ecodes as e
import evdev
import time

# Connect to the first panel
panel1 = GT911_Panel(i2c_address = 0x5d, int_pin = 18, rst_pin = 26)
if not panel1.connect():
    print("Failed connection P1")
    input("Press enter to continue")
panel1.start_reading()

TOUCH_RESOLUTION = (1024, 600)
SQUARE = 1024

squareAbsInfo = AbsInfo(value=0, min=0, max=SQUARE, fuzz=0, flat=0, resolution=31)

# Set up the touch emulation device
cap = {
    e.EV_KEY : [e.KEY_A, e.KEY_B, e.BTN_LEFT, e.BTN_MOUSE, e.BTN_MIDDLE, e.BTN_RIGHT],
    e.EV_ABS : [
        (e.ABS_X, squareAbsInfo),
        (e.ABS_Y, squareAbsInfo),
        (e.ABS_MT_SLOT, AbsInfo(value=0, min=0, max=10, fuzz=0, flat=0, resolution=0)),
        (e.ABS_MT_POSITION_X, squareAbsInfo),
        (e.ABS_MT_POSITION_Y, squareAbsInfo),
        (e.ABS_MT_TRACKING_ID, AbsInfo(value=0, min=0, max=9999, fuzz=0, flat=0, resolution=0)) ]
}
ui = UInput(cap, name='send_touch_to_linux', version=0x3)


# Run foreveh
while (True):
    # Only tracks one input rn
    if (panel1.fresh == True):
        # swap x and y
        (y1, x1) = panel1.coords()

        # Close touch event
        if not x1:
            ui.write(e.EV_ABS, e.ABS_MT_SLOT, 0)
            ui.write(e.EV_ABS, e.ABS_MT_TRACKING_ID, -1) # Can be anything, as long as each touch is unique
            ui.syn()
            
        # Update touch event / create new touch event
        else:
            ui.write(e.EV_ABS, e.ABS_MT_SLOT, 0)
            ui.write(e.EV_ABS, e.ABS_MT_TRACKING_ID, 45) # Can be anything, as long as each touch is unique
            ui.write(e.EV_ABS, e.ABS_MT_POSITION_X, x1[0])
    # Read data
    # If fresh
        # if empty
            # set ID negavite
        # if new touch down
            # set "unique" ID (really just whatever the slot is)
            # update evdev with the position
        # else
            # update evdev with the positionN_X, x1[0])
            ui.write(e.EV_ABS, e.ABS_MT_POSITION_Y, y1[0])
            ui.syn()
