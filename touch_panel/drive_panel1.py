"""
send touch inputs from the GT911 to the linux userspace
"""

import os
import time
from gt911_panel import GT911_Panel
from evdev import UInput, AbsInfo, ecodes as e

# Constants
i2c_address = 0x5d
int_pin = 18
rst_pin = 26

TOUCH_RESOLUTION = (1024, 600)
SQUARE = 1024
Y_FUDGE = 175.64/163.2 #ratio of two dimensions
REFRESH_DIST = 40

# Global variables
uuid = 1

def MapTouchToDisplay(x, y) -> [int, int]:
    """
    Return: [x_prime, y_prime]
    """

    # Swap x & y, then invert y
    t = y
    y = x
    x = t
    y = SQUARE - y

    # Get rid of dead space at bottom
    y = y*Y_FUDGE

    # Shift touch down a little
    y = y + 20
    x = x + 20

    return [int(x), int(y)]


def ReleaseTouch(ui, MT_SLOT) -> None:
    ui.write(e.EV_ABS, e.ABS_MT_SLOT, MT_SLOT)
    ui.write(e.EV_ABS, e.ABS_MT_TRACKING_ID, -1) # Can be anything, as long as each touch is unique
    ui.syn()


def StartTouch(ui, MT_SLOT, x_in, y_in) -> int:
    # Be lazy with it
    global uuid
    ID = uuid
    uuid = uuid + 1

    # Check if we should refresh the screen
    if ((x_in < REFRESH_DIST) and (y_in < REFRESH_DIST)):
        full_refresh_memory = open("/dev/shm/full_refresh.bin", "wb")
        full_refresh_memory.write(b'\x01')
        full_refresh_memory.flush()
        time.sleep(1)
        full_refresh_memory.seek(0)
        full_refresh_memory.write(b'\x00')
        full_refresh_memory.flush()
    else: 
        [x, y] = MapTouchToDisplay(x_in, y_in)

        # Flush the slot
        ui.write(e.EV_ABS, e.ABS_MT_SLOT, MT_SLOT)
        ui.write(e.EV_ABS, e.ABS_MT_TRACKING_ID, -1) 
        ui.write(e.EV_ABS, e.ABS_MT_POSITION_X, x) # fixes issue where previous touches connect to eachother
        ui.write(e.EV_ABS, e.ABS_MT_POSITION_Y, y)
        ui.syn()

        # Create the slot
        ui.write(e.EV_ABS, e.ABS_MT_SLOT, MT_SLOT)
        ui.write(e.EV_ABS, e.ABS_MT_TRACKING_ID, ID) # Can be anything, as long as each touch is unique
        ui.syn()

        # Write the position data
        ui.write(e.EV_ABS, e.ABS_MT_POSITION_X, x)
        ui.write(e.EV_ABS, e.ABS_MT_POSITION_Y, y)
        ui.syn()
    return ID


def UpdateTouch(ui, MT_SLOT, ID, x, y) -> None:
    # Swap x & y, then invert y
    # t = y
    # y = x
    # x = t
    # y = SQUARE - y
    [x, y] = MapTouchToDisplay(x, y)

    ui.write(e.EV_ABS, e.ABS_MT_SLOT, MT_SLOT)
    ui.write(e.EV_ABS, e.ABS_MT_TRACKING_ID, ID)
    ui.syn()
    
    ui.write(e.EV_ABS, e.ABS_MT_POSITION_X, x)
    ui.write(e.EV_ABS, e.ABS_MT_POSITION_Y, y)
    ui.syn()


# Connect to the first panel
panel1 = GT911_Panel(i2c_address = i2c_address, int_pin = int_pin, rst_pin = rst_pin)

while not panel1.connect():
    print("Failed connection Panel 1. Trying again")
    time.sleep(0.3)

time.sleep(1)
panel1.start_reading()


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
ui = UInput(cap, name='Touch Panel 1', version=0x3)


print("starting")


# Initialize
touch_id = None
TouchDict = dict() #"PanelTouchID" : "evdev_MT_slot"

# Send taps to Linux userspace
while (True):
    # print("Is this thing on?")
    # time.sleep(0.1)
    if (panel1.fresh == True):

        # Nab our new data
        panel_data = panel1.coords()

        for new_slot in panel_data:
            # Update the specified touch with new coords
            if new_slot in TouchDict:
                UpdateTouch(ui, new_slot, TouchDict[new_slot], panel_data[new_slot][0], panel_data[new_slot][1])

            # Do nothing
            elif new_slot == None:
                continue

            # Create new touch-down event for the new data
            else:
                mt_track_id = StartTouch(ui, new_slot, panel_data[new_slot][0], panel_data[new_slot][1])
                TouchDict[new_slot] = mt_track_id

        for old_touch_ID in list(TouchDict):
            # If old info is not seen in new list, we assume it's been removed
            if old_touch_ID not in panel_data:
                ReleaseTouch(ui, old_touch_ID)
                TouchDict.pop(old_touch_ID)
