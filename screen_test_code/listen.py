import time
import os

filepath = "/dev/shm/trigger.bin"

if not os.path.exists(filepath):
    with open(filepath, "wb") as f:
        f.write(b'\x00')

with open(filepath, "r+b") as f:
    while True:
        f.seek(0)
        
        if f.read(1) == b'\x01':
            print("test")
            
            f.seek(0)
            f.write(b'\x00')
            f.flush()
            
        time.sleep(0.05)