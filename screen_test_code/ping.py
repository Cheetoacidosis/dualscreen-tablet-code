import os

filepath = "/dev/shm/trigger.bin"

if not os.path.exists(filepath):
    with open(filepath, "wb") as f:
        f.write(b'\x00')

with open(filepath, "r+b") as f:
    f.seek(0)
    f.write(b'\x01')
    f.flush()