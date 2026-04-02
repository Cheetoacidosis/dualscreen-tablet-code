

        
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
YMAX = 800
XMAX = YMAX
p = (480/2, YMAX/2)
# p = (0,0)
r = 40
margin = 40

TOUCH_RESOLUTION = (800, 800)
SQUARE = 800

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

ui = UInput(cap, name='example-device', version=0x3)

# Enough time to get away lol
time.sleep(5)

# move touch 
while(True):
    # Initialize new touch event
    ui.write(e.EV_ABS, e.ABS_MT_SLOT, 0)
    ui.write(e.EV_ABS, e.ABS_MT_TRACKING_ID, 45) # Can be anything, as long as each touch is unique
    ui.syn()

    # Draw a circle
    for i in range(314*2):
        x = int(r*np.cos(i/100) + p[0])
        y = int(r*np.sin(i/100) + p[1])

        ui.write(e.EV_ABS, e.ABS_MT_SLOT, 0)
        ui.write(e.EV_ABS, e.ABS_MT_POSITION_X, x)
        ui.write(e.EV_ABS, e.ABS_MT_POSITION_Y, y)
        ui.syn()
        time.sleep(0.001)

    time.sleep(0.01)
    # End touch event
    ui.write(e.EV_ABS, e.ABS_MT_SLOT, 0)
    ui.write(e.EV_ABS, e.ABS_MT_TRACKING_ID, -1)
    ui.syn()

    time.sleep(1)


    # Initialize second touch event
    ui.write(e.EV_ABS, e.ABS_MT_SLOT, 1)
    ui.write(e.EV_ABS, e.ABS_MT_TRACKING_ID, 46) # Can be anything, as long as each touch is unique
    ui.syn()

    # Draw a circle
    for i in range(314*2):
        x = int(r*np.cos(i/100) + p[0])
        y = int(r*np.sin(i/100) + p[1])

        ui.write(e.EV_ABS, e.ABS_MT_SLOT, 1)
        ui.write(e.EV_ABS, e.ABS_MT_POSITION_X, x-margin)
        ui.write(e.EV_ABS, e.ABS_MT_POSITION_Y, y-margin)
        ui.syn()
        time.sleep(0.001)

    time.sleep(0.01)
    # End touch event
    ui.write(e.EV_ABS, e.ABS_MT_SLOT, 1)
    ui.write(e.EV_ABS, e.ABS_MT_TRACKING_ID, -1)
    ui.syn()
    
    time.sleep(1)








    # Draw a square around the bounds
    # ui.write(e.EV_ABS, e.ABS_MT_SLOT, 0)
    # ui.write(e.EV_ABS, e.ABS_MT_POSITION_X, XMAX - margin)
    # ui.write(e.EV_ABS, e.ABS_MT_POSITION_Y, YMAX - margin)
    # ui.syn()
    # time.sleep(0.01)

    # ui.write(e.EV_ABS, e.ABS_MT_SLOT, 0)
    # ui.write(e.EV_ABS, e.ABS_MT_POSITION_X, margin)
    # ui.write(e.EV_ABS, e.ABS_MT_POSITION_Y, YMAX - margin)
    # ui.syn()
    # time.sleep(0.01)

    # ui.write(e.EV_ABS, e.ABS_MT_SLOT, 0)
    # ui.write(e.EV_ABS, e.ABS_MT_POSITION_X, margin)
    # ui.write(e.EV_ABS, e.ABS_MT_POSITION_Y, margin)
    # ui.syn()
    # time.sleep(0.01)

    # ui.write(e.EV_ABS, e.ABS_MT_SLOT, 0)
    # ui.write(e.EV_ABS, e.ABS_MT_POSITION_X, XMAX - margin)
    # ui.write(e.EV_ABS, e.ABS_MT_POSITION_Y, margin)
    # ui.syn()
    # time.sleep(0.01)





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