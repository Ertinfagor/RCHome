#!/usr/bin/python
import time
b = [0x1,0,0,0,0,0,0,0,0,0,0xff,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
# Open a file
print b[8]
fo = open("/Log.txt", "a+")
for item in b:
	fo.write("%s" % item)
	print
fo.flush();
time.sleep(1);
print fo.readline();
#{0x1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,i,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
