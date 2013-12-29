#!/usr/bin/env python


import subprocess
import time
process = subprocess.Popen(['../controller/terminal'], shell=False, stdin=subprocess.PIPE, stdout=subprocess.PIPE,universal_newlines=True)


process.stdin.write('1\n')
print process.stdout.readline()
