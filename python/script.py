#!/usr/bin/env python


import subprocess

process = subprocess.Popen(['../controller/terminal'], shell=False, stdin=subprocess.PIPE, stdout=subprocess.PIPE,universal_newlines=True)
print process.stdout.read()
print "Test2"

#process.stdin.write('1\n')
process.communicate(input="1\n")
print "Test1"
print process.stdout.readline()
print "Test2"

