###########################################################################
#
#   Author: Alec Ng
#   Purpose: Main program flow for the pi side
#   Requires: run this script with root access to access GPIOs on pi.
#       assumes you've followed steps in the scripts in recognizer_generator
#
###########################################################################

import os, sys, time
# sms
from twilio.rest import TwilioRestClient
# db
import psycopg2
# facerec
import cv2
import numpy as np
from PIL import Image
sys.path.insert(0, '/home/pi/Desktop/Home-Security/Python/face_rec/training-utilities')
import imcrop
from getManipImages import preprocess
from sizeToFace import align_single
# DE2 - Pi communication
import exmod
from DE2_success_failure import gpio_setup
from DE2_success_failure import send_accept
from DE2_success_failure import send_reject

# Code to send msg comes from https://www.twilio.com/docs/quickstart/python/sms/sending-via-rest
# From number: Twilio phone number (obtained when the account is created on the website)
# To number - number to send message to
def sendsms(msg):   
    account_sid = "AC18e1853bd28bd96c53283730030d88d4"
    auth_token = "e75f3b53826b9aec8b8aeb47d0cb96ba"
    client = TwilioRestClient(account_sid, auth_token)
    message = client.messages.create(to="+17787733779", from_="+16042567685",
    body=msg)
    print 'SMS MESSAGE SENT'
    
if __name__ == '__main__':
        
    #########################################
    #  Initialization
    #########################################

    # connect to postgreSQL database
    conn = psycopg2.connect(database="securitysystem", user="root")
    cur = conn.cursor()

    # load face cascade for face detection
    faceCascade = cv2.CascadeClassifier("haarcascade_frontalface_default.xml")
    picCount = 0

    # create a matcher object for face recognition
    # 0 requires an identical img; higher the num, higher the err tolerence
    threshold_val = 120
    matcher = cv2.face.createFisherFaceRecognizer(threshold=threshold_val)

    # load trained fisher set
    print "Loading trained Fisher model, this will take a while..."
    matcher.load("trainedFisherModel.xml")
    print "Trained model loaded."

    gpio_setup()

    while True:

        #########################################
        #  DE2 -> Pi Matrix Keypad routine
        #########################################

        # TODO: call routine and assign to user_ID
        
        print "Waiting for user ID via keypad..."
        raw_ID = exmod.get_data("aa")
        user_ID = str(raw_ID[0]) + str(raw_ID[1]) + str(raw_ID[2]) + str(raw_ID[3])
        print user_ID
        checkPath = 'recognizer_generator/Image-Process/' + user_ID
    
        # if user_ID exists, there will be a directory here...
        if os.path.isdir(checkPath) != True:
            print "Invalid PIN Code"
            record_id = str(user_ID) + '\t'
            # add to log
            log_str = "insert into log (DATE,ID,IMAGE) VALUES(now(), "
            log_str = log_str + "'" +  user_ID + "', '" + "invalid key')"
            cur.execute(log_str)
            conn.commit()
            send_reject()
            continue

        send_accept()
        
        #########################################
        #  DE2 -> Pi Image Routine
        #########################################

        # check if DE2 is sending a picture, gets it, constructs an image, saves
        # it in a folder called "temp" as "temp.jpg"
        print "Waiting to take picture..."
        exmod.get_data("temp")
        # get_data saves in curr dir, move to temp
        picCount += 1
        pic_Rename = "temp/temp" + str(picCount) + ".jpg"
        align_path = "/home/pi/Desktop/Home-Security/Python/face_rec/" + pic_Rename
        log_path = "/home/pi/Desktop/Home-Security/Python/face_rec/" + pic_Rename
        os.rename("temp.ppm", pic_Rename)
        
        #########################################
        #  Face Detection
        #########################################
       
        # detect if there is a face in the received image
        de2_received_image = cv2.imread(pic_Rename, 0)
        faces = faceCascade.detectMultiScale(de2_received_image)

        # if success, continue, if failure, go back to waiting for another pic
        if len(faces) > 1 or len(faces) == 0:
            print "Error in detecting face.."
            record_id = user_ID + "\t"
            # add to log
            log_str = "insert into log (DATE,ID,IMAGE) VALUES(now(), "
            log_str = log_str + "'" +  user_ID + "', '" + log_path + "')"
            cur.execute(log_str)
            conn.commit()
            send_reject()
            continue
        elif len(faces) == 1:
            print "Face successfully found!"
        
        #########################################
        #  Face Recognition
        #########################################

        # align face same way as set: looks for temp.jpg, outputs it as 1.jpg
        align_single(align_path)
        # preprocess received image in same manner as trained set
        manip_de2_image = preprocess(Image.open("temp/1.jpg"))
        cv2.imwrite("temp/1.jpg", manip_de2_image)

        # match picture against trained set, see if it yields same label
        [p_label, p_confidence] = matcher.predict(manip_de2_image)
        print "Fisher Predicted label = %d (confidence=%.2f)" % (p_label, p_confidence)

        # -1 is no match to any (confidence level > threshold)
        id_matcher = int(user_ID)
        if p_label < 0 or p_label != id_matcher: 
            isMatch = False
        else:
            isMatch = True

        # send results back to DE2. Done loop.
        if isMatch is True:
            print "It's a match!"
            send_accept()
        elif isMatch is False:
            print "It's not a match.."
            record_id = user_ID + "\t"
            # add to log
            log_str = "insert into log (DATE,ID,IMAGE) VALUES(now(), "
            log_str = log_str + "'" +  user_ID + "', '" + log_path + "')"
            cur.execute(log_str)
            conn.commit()
            sendsms("Warning - Unauthorized attempt")
            send_reject()
