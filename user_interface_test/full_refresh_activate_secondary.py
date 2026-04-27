
import time

full_refresh_memory = open("/dev/shm/full_refresh2.bin", "wb")
full_refresh_memory.write(b'\x01')
full_refresh_memory.flush()
time.sleep(1)
full_refresh_memory.seek(0)
full_refresh_memory.write(b'\x00')
full_refresh_memory.flush()