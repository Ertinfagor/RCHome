#!/usr/bin/env python
import subprocess

process = subprocess.Popen(['top'], shell=False, stdin=subprocess.PIPE, stdout=subprocess.PIPE,universal_newlines=True)

print process.stdout.read()

