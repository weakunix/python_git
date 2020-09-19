import os
from stat import S_IREAD, S_IRGRP, S_IROTH

os.remove("cow.txt")
h = open("cow.txt", "w+")
h.write("hi")
h.close()
os.chmod("cow.txt", S_IREAD)
