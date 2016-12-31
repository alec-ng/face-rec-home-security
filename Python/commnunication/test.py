#!/usr/bin/python
import RPi.GPIO as GPIO
import time

def main():
	gpio_setup()	
	
	while True:
		
		get_data()
		print( "DONE" )

def get_data():
	
	x = 0 
	length = 0
	
	type = get_type()
	length = get_length()

	print( "TYPE" )
	print( type )

	print( "LENGTH" )
	print( length )

	print( "DATA" )

	for x in xrange(0,length):
		
		print(chr(do_transfer()))
		#do_transfer()

def get_type():
	return do_transfer()

def get_length():
	
	i = 0 
	length = 0

	for i in range(0,4):
		
		if( i == 0 ):
			length |= (do_transfer())
		elif( i == 1 ):
			length |= (do_transfer() << 8)
		elif( i == 2 ):
			length |= (do_transfer() << 16)
		elif( i == 3 ):
			length |= (do_transfer() << 24)

	return length


def do_transfer(): 
	
	#print("waiting for valid HIGH")
	while( not GPIO.input(23) ):
		x = 1

	#print("reading data")
	byte = piece_together_byte() 
	#print( byte )

	#print("ack HIGH")
	GPIO.output(18,GPIO.HIGH)

	#print("waiting for valid LOW")
	while( GPIO.input(23) ):
		x = 2
		
	#print("ack LOW")		
	GPIO.output(18,GPIO.LOW)

	return byte

def gpio_setup():

	GPIO.setmode(GPIO.BCM)
	GPIO.cleanup()
	GPIO.setwarnings(False)
	GPIO.setup(21,GPIO.IN)
	GPIO.setup(20,GPIO.IN)
	GPIO.setup(16,GPIO.IN)
	GPIO.setup(12,GPIO.IN)
	GPIO.setup(7,GPIO.IN)
	GPIO.setup(8,GPIO.IN)
	GPIO.setup(25,GPIO.IN)
	GPIO.setup(24,GPIO.IN)
	GPIO.setup(23,GPIO.IN)
	GPIO.setup(18,GPIO.OUT)
	GPIO.output(18,GPIO.LOW)

def get_char():

	byte = piece_together_byte()
	return chr(byte)

def piece_together_byte():
	
	byte = 0

	if( GPIO.input(12) ):
		byte |= 0x01
	if( GPIO.input(7) ):
		byte |= 0x02
	if( GPIO.input(16) ):
		byte |= 0x04
	if( GPIO.input(8) ):
		byte |= 0x08
	if( GPIO.input(20) ):
		byte |= 0x10
	if( GPIO.input(25) ):
		byte |= 0x20
	if( GPIO.input(21) ):
		byte |= 0x40
	if( GPIO.input(24) ):
		byte |= 0x80

	return byte

	


main()