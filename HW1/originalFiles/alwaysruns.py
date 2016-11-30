#!/usr/bin/python


import time
import os
sleepTime = 3;
while 1:
    time.sleep(sleepTime); 
    print 'I have slept for',sleepTime,'seconds. my pid is: ',os.getpid()

