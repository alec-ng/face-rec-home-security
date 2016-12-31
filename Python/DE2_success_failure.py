import RPi.GPIO as GPIO

def gpio_setup():
        GPIO.setmode(GPIO.BCM)
        GPIO.cleanup()
        GPIO.setwarnings(False)

        GPIO.setup(23,GPIO.IN)
        GPIO.setup(26,GPIO.OUT)
        GPIO.setup(19,GPIO.OUT)
        GPIO.output(26,GPIO.LOW)
        GPIO.output(19,GPIO.LOW)


def send_accept():
    #wait for valid high from DE2
    while(not GPIO.input(23)):
        pass
    #set accept signal
    GPIO.output(26,GPIO.HIGH)
    #wait for valid low from DE2
    while(GPIO.input(23)):
        pass
    #set accept signal back to low
    GPIO.output(26,GPIO.LOW)
    

def send_reject():
    #wait for valid high from DE2
    while(not GPIO.input(23)):
        pass
    #set reject signal high
    GPIO.output(19,GPIO.HIGH)
    #wait for valid low from DE2
    while(GPIO.input(23)):
        pass
    #set reject signal back to low
    GPIO.output(19,GPIO.LOW)