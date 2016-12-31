#!/usr/bin/python
import time,os
from datetime import datetime
from datetime import timedelta
import logging

#function adds a new record to the log file
def addrecord(record):
	global logger
	logger.critical(record)

def createlog(currentname):
	#set the general parameters for the log file: structure, name, mode, and importance level of the events
	#logging.basicConfig(format='%(message)s', filemode='w', level=logging.CRITICAL)
	global logger
	logger = logging.getLogger('scheduler')
	logger.setLevel(logging.CRITICAL)
	# create file handler which logs CRITICAL messages
	fh = logging.FileHandler(currentname)
	fh.setLevel(logging.CRITICAL)
	formatter=logging.Formatter('%(message)s')
	fh.setFormatter(formatter)
	# add the handler to the logger
	logger.addHandler(fh)
	print currentname
		
if __name__ == '__main__':
	createlog(currentname)
