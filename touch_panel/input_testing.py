from evdev import UInput, AbsInfo, ecodes as e
import evdev
import time

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

cap = {
    # e.EV_SYsN : 0,
    e.EV_KEY : [e.KEY_A, e.KEY_B],
    e.EV_ABS : [
        (e.ABS_X, AbsInfo(value=0, min=0, max=255,
                          fuzz=0, flat=0, resolution=0)),
        (e.ABS_Y, AbsInfo(0, 0, 255, 0, 0, 0)),
        (e.ABS_MT_POSITION_X, (0, 128, 255, 0)) ]
}

ui = UInput(cap, name='example-device', version=0x3)

print(ui)

print(ui.capabilities())
# ui.write(e.EV_KEY, e.KEY_A, 1)  # KEY_A down
# ui.write(e.EV_KEY, e.KEY_A, 0)  # KEY_A up
# ui.syn()

# print(ui._capabilities())

# # move mouse cursor
ui.write(e.EV_ABS, e.ABS_X, 20)
ui.write(e.EV_ABS, e.ABS_Y, 20)
ui.syn()