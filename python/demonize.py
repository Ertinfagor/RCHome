#!/usr/bin/python
import time
# Open a file
fo = open("/Log.txt", "a+")
fo.write( "Python is a great language.\nYeah its great!!\n");
fo.flush();
time.sleep(1);
print fo.readline();
