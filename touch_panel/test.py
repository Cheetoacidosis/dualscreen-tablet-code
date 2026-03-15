from gt911_panel import GT911_Panel

pog = GT911_Panel(Address = 0x14, int_pin = 18, rst_pin = 26)

pog.Start()

while(1):
    gay = pog.x_coords
    yag = pog.y_coords

    print(len(gay))