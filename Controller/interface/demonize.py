#!/usr/bin/python
import time
# Open a file
fo = open("/Log.txt", "a+")
fo.write("0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0")
fo.flush();
time.sleep(2);
print fo.readline();
