# from evdev import UInput, AbsInfo, ecodes as e
# import evdev
# import time

# ui = UInput()
# while(True):
#     ui.write(e.EV_KEY, e.KEY_A, 1)  # KEY_A down
#     ui.write(e.EV_KEY, e.KEY_A, 0)  # KEY_A up
#     ui.syn() #Events are queued until a syncronization event is recieved with .syn()
#     time.sleep(1.1)

# ui.close()

# print (evdev.list_devices())
# devices = [evdev.InputDevice(path) for path in evdev.list_devices()]
# for device in devices:
#     print(device.path, device.name, device.phys)

# ui.close()


# from evdev import UInput, AbsInfo, ecodes as e

# cap = {
#     # e.EV_SYsN : 0,
#     e.EV_KEY : [e.KEY_A, e.KEY_B, e.BTN_LEFT, e.BTN_MOUSE, e.BTN_MIDDLE, e.BTN_RIGHT],
#     e.EV_ABS : [
#         (e.ABS_X, AbsInfo(value=0, min=0, max=255,
#                           fuzz=0, flat=0, resolution=0)),
#         (e.ABS_Y, AbsInfo(0, 0, 255, 0, 0, 0)),
#         (e.ABS_MT_POSITION_X, AbsInfo(value=0, min=0, max=2940, fuzz=0, flat=0, resolution=31)) ]
        
#     # ('EV_KEY', 1): [(('BTN_LEFT', 'BTN_MOUSE'), 272), ('BTN_RIGHT', 273), ('BTN_MIDDLE', 274), ('BTN_SIDE', 275), ('BTN_EXTRA', 276), ('BTN_FORWARD', 277), ('BTN_BACK', 278), ('BTN_TASK', 279) ]
# }




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