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

TOUCH_RESOLUTION = (1024, 600)
SQUARE = 1024
uuid = 1

def ReleaseTouch(ui, MT_SLOT) -> None:
    print("releasing touch ", MT_SLOT)
    ui.write(e.EV_ABS, e.ABS_MT_SLOT, MT_SLOT)
    ui.write(e.EV_ABS, e.ABS_MT_TRACKING_ID, -1) # Can be anything, as long as each touch is unique
    ui.syn()


def StartTouch(ui, MT_SLOT, x, y) -> int:
    # Be lazy with it
    global uuid
    ID = uuid
    uuid = uuid + 1
    print("starting touch ", MT_SLOT, " ID:", ID)
    # Swap x & y, then invert y
    t = y
    y = x
    x = t
    y = SQUARE - y

    # Flush the slot
    ui.write(e.EV_ABS, e.ABS_MT_SLOT, MT_SLOT)
    ui.write(e.EV_ABS, e.ABS_MT_TRACKING_ID, -1) 
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
    print("moving touch ", MT_SLOT)
    # Swap x & y, then invert y
    t = y
    y = x
    x = t
    y = SQUARE - y

    ui.write(e.EV_ABS, e.ABS_MT_SLOT, MT_SLOT)
    ui.write(e.EV_ABS, e.ABS_MT_TRACKING_ID, ID)
    ui.syn()
    
    ui.write(e.EV_ABS, e.ABS_MT_POSITION_X, x)
    ui.write(e.EV_ABS, e.ABS_MT_POSITION_Y, y)
    ui.syn()


# Connect to the first panel
panel1 = GT911_Panel(i2c_address = 0x5d, int_pin = 18, rst_pin = 26)

while not panel1.connect():
    print("Failed connection Panel 1")
    input("Press enter to try again")

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
ui = UInput(cap, name='send_touch_to_linux', version=0x3)

# print(type(panel1.coords()))
print("starting")
# print(panel1.connected)

# Initialize
touch_id = None
TouchDict = dict() #"PanelTouchID" : "evdev_MT_slot"


# Run foreveh
while (True):



    if (panel1.fresh == True):

        # Nab our new data
        panel_data = panel1.coords()
        # touch_id = panel1.track_ids

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

        # TouchDictCopy = TouchDict
        for old_touch_ID in list(TouchDict):
            # If old info is not seen in new list, we assume it's been removed
            if old_touch_ID not in panel_data:
                ReleaseTouch(ui, old_touch_ID)
                TouchDict.pop(old_touch_ID)






        # print("panel fresh")
        # swap x and y
        # (y1, x1) = panel1.coords()
        # old_touch_ids = touch_id
        # touch_id = panel1.track_ids

        # # print("fresh")


        # # invert y
        # try:
        #     y1[0] = SQUARE - y1[0]
        # except:
        #     # print("nothing to invert")
        #     nothing = None

        

        # if touch_id and not old_touch_ids:
        #     # new touch
        #     # print("New touch")
        #     ui.write(e.EV_ABS, e.ABS_MT_SLOT, 0)
        #     ui.write(e.EV_ABS, e.ABS_MT_TRACKING_ID, 45) # Can be anything, as long as each touch is unique
        #     ui.syn()

        #     ui.write(e.EV_ABS, e.ABS_MT_POSITION_X, x1[0])
        #     ui.write(e.EV_ABS, e.ABS_MT_POSITION_Y, y1[0])
        #     ui.syn()

        # elif (not touch_id) and old_touch_ids:
        #     # Touch released
        #     print("touch released")
        #     ui.write(e.EV_ABS, e.ABS_MT_SLOT, 0)
        #     ui.write(e.EV_ABS, e.ABS_MT_TRACKING_ID, -1) # Can be anything, as long as each touch is unique
        #     ui.syn()

        # elif touch_id != old_touch_ids:
        #     # Touch moved
        #     ui.write(e.EV_ABS, e.ABS_MT_SLOT, 0)
        #     ui.write(e.EV_ABS, e.ABS_MT_POSITION_X, x1[0])
        #     ui.write(e.EV_ABS, e.ABS_MT_POSITION_Y, y1[0])
        #     ui.syn()


