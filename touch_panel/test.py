import os
import time
from gt911_panel import GT911_Panel

panel1 = GT911_Panel(i2c_address = 0x14, int_pin = 18, rst_pin = 26)
if not panel1.connect():
    print("Failed connection P1")
    input("Press enter to continue")
panel1.start_reading()

panel2 = GT911_Panel(i2c_address = 0x5d, int_pin = 23, rst_pin = 24)
if not panel2.connect():
    print("Failed connection P2")
    input("Press enter to continue")
panel2.start_reading()

print("Touch the screen ")

while (True):

    # Read and display data
    if ((panel1.fresh == True) or (panel2.fresh == True)):
        (x1, y1) = panel1.coords()
        (x2, y2) = panel2.coords()
        os.system('cls' if os.name == 'nt' else 'clear')
        print ("Panel 1")
        for i in range(len(x1)):
            print(str(x1[i]) + ", " + str(y1[i]))
        print("Panel 2")
        for i in range(len(x2)):
            print(str(x2[i]) + ", " + str(y2[i]))
    
    # Attempt to hot-reconnect
    if (panel1.connected == False): 
        time.sleep(1)
        if (panel1.connect()):
            print("Panel 1 reconnected")
        else:
            print("Panel 1 disconnected")

    if (panel2.connected == False): panel2.connect()
    


    time.sleep(0.01)