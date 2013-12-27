#!/usr/bin/env python


import subprocess

process = subprocess.Popen(['../controller/terminal'], shell=False, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
process.stdin.write('2\r\n')
print "Test1"
print process.stdout.readline()
print "Test2"

