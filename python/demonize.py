#!/usr/bin/python
import time
# Open a file
fo = open("/Log.txt", "a+")
fo.write( "0000000000000000000000000000000\n");
fo.flush();
time.sleep(1);
print fo.readline();
