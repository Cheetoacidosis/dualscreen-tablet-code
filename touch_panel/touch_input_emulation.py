

        
"""
Emulate a touch panel with a single point. Draws a circle every second
For Qt to recognize it, you need to add the command-line argument
"-plugin EvdevTouch:/dev/input/eventX", where X depends on your local HW setup.
This would not be necessary if I knew the secret sauce required for Qt to realize this is a touch device

Additionally, all widgets that are to be touch-accessible need to have specific attribute
example:
ui->pdfViewWidget->setAttribute(Qt::WA_AcceptTouchEvents, true);
"""
from evdev import UInput, AbsInfo, ecodes as e
import evdev
import time
import numpy as np

# Radius and center point for drawing a circle with the emulated touch panel
p = (1128, 752)
r = 250

cap = {
    e.EV_KEY : [e.KEY_A, e.KEY_B, e.BTN_LEFT, e.BTN_MOUSE, e.BTN_MIDDLE, e.BTN_RIGHT],
    e.EV_ABS : [
        (e.ABS_X, AbsInfo(value=0, min=0, max=2256, fuzz=0, flat=0, resolution=31)),
        (e.ABS_Y, AbsInfo(0, 0, 1504, 0, 0, 31)),
        (e.ABS_MT_SLOT, AbsInfo(value=0, min=0, max=10, fuzz=0, flat=0, resolution=0)),
        (e.ABS_MT_POSITION_X, AbsInfo(value=0, min=0, max=2256, fuzz=0, flat=0, resolution=31)),
        (e.ABS_MT_POSITION_Y, AbsInfo(value=0, min=0, max=1504, fuzz=0, flat=0, resolution=31)),
        (e.ABS_MT_TRACKING_ID, AbsInfo(value=0, min=0, max=9999, fuzz=0, flat=0, resolution=0)) ]
}

ui = UInput(cap, name='example-device', version=0x3)

# Enough time to get away lol
time.sleep(5)

# move touch 
while(True):
    # Initialize new touch event
    ui.write(e.EV_ABS, e.ABS_MT_SLOT, 0)
    ui.write(e.EV_ABS, e.ABS_MT_TRACKING_ID, 45) # Can be anything, as long as each touch is unique
    # ui.write(e.EV_KEY, e.BTN_LEFT, 1) # "Pen down"
    ui.syn()

    # Draw a circle
    for i in range(314*2):
        x = int(r*np.cos(i/100) + p[0])
        y = int(r*np.sin(i/100) + p[1])

        ui.write(e.EV_ABS, e.ABS_MT_SLOT, 0)
        ui.write(e.EV_ABS, e.ABS_MT_POSITION_X, x)
        ui.write(e.EV_ABS, e.ABS_MT_POSITION_Y, y)
        ui.syn()

    time.sleep(0.01)
    # End touch event
    ui.write(e.EV_ABS, e.ABS_MT_SLOT, 0)
    ui.write(e.EV_ABS, e.ABS_MT_TRACKING_ID, -1)
    # ui.write(e.EV_KEY, e.BTN_LEFT, 0) # "pen up"
    ui.syn()
    time.sleep(1)









if (False):
    """
    Minimal working example of relative mouse movement
    """
    from evdev import UInput, AbsInfo, ecodes as e
    import evdev
    import time

    cap = {e.EV_REL: [e.REL_X, e.REL_Y],e.EV_KEY: [e.BTN_LEFT]} 

    ui = UInput(cap, name='example-device', version=0x3)

    # move mouse cursor
    while(True):
        ui.write(e.EV_REL, e.REL_X, 20)
        ui.write(e.EV_REL, e.REL_Y, 20)
        ui.syn()
        time.sleep(0.05)