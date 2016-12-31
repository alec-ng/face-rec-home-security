#!/usr/bin/python
import RPi.GPIO as GPIO
import time


#Does the whole process of getting all the bytes and reconstructing the image and then saving it. 
#Takes in a filename that you want the file saved to. 
#Ready for extension with type and length.
def get_data(filename):
       
        #Used as loop counter
        x = 0
        #Used to store length value
        length = 0
       
        #Do initial transfer to get the type
        type = do_transfer()

	#print TYPE and received type
        print( "TYPE" )
        print( type )
	
	#Incoming is the list that holds received bytes
	Incoming = list()

	#Reads 4 bytes (the size of a long) as the length and prints to screen.
        for x in xrange(0,4):

                if( x == 0 ):
                        length |= (do_transfer())
                elif( x == 1 ):
                        length |= (do_transfer() << 8)
                elif( x == 2 ):
                        length |= (do_transfer() << 16)
                elif( x == 3 ):
                        length |= (do_transfer() << 24)

        print( "LENGTH" )
        print( length )

        print( "DATA" )

	#Receives length number of bytes and puts them in Incoming array.
        for x in xrange(0,length):

                Incoming.append(do_transfer())

        print "DONE"

        Outgoing = list()

	#Converting from DE2 pixel buffer format to image format
        for x in xrange(0, length/2):
                Outgoing.append((Incoming[x*2] & 0b00011111) * 8)
                Outgoing.append(((Incoming[(2*x)+1] & 0b00000111) * 32) + ((Incoming[2*x] & 0b11100000) / 8))
                Outgoing.append(Incoming[(2*x) + 1] & 0b11111000)
	
	print "16 to 24 Conversion Finished"

	#Creates image and saves to directory
        #make_Img( Outgoing, filename )

	print "MADE IMG"


#Does the GPIO transfer of one byte.
def do_transfer():

        #print("sleep")
        #time.sleep(1)

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

#Setup function to be called before any GPIO functions
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

#Takes the input of the GPIO and reconstruct the byte that is being sent by the DE2
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

#main not used but shows the proper order of function call

def main():
        gpio_setup()
       
        while True:
       
                get_data()


#Unused function.
"""
def get_char():
        byte = piece_together_byte()
        return chr(byte)
"""
