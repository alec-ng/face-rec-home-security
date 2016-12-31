###########################################################################
#
#   Author: Alec Ng
#   Brief: Connects to the DE2 and continuously receives images and 
#       saves them in directories corresponding to the user_id passed in. 
#       Requires: userID dir in "Image-Raw" exists
#   Requires: root access for GPIO communication
#
###########################################################################

import os
import sys
import numpy as np
import exmod

# method to call if using this script in create_user.py
def new_user_rawImgs(user_ID):
    dest_path = "Image-Raw/" + user_ID
    x = 1

    while True:
        filename = str(x) + ".jpg"
        target_filename = "Image-Raw/" + user_ID + "/" + filename
        print "Take picture now -- "
        exmod.get_data(filename)
        os.rename("temp.ppm", target_filename)
        print "Iimage count: %s" % x
        x += 1
        check_out = raw_input("Enter 1 to stop taking pictures, anything otherwise: ")
        if check_out is '1':
            break;

    print "Done taking pictures."

# method used if running independently (mainly for testing purposes)
def get_rawImgs():

    user_id = raw_input("Enter userID, the folder to save the raw images to: ")
    start_num = raw_input("Enter a number val to start naming your images: ")
    dest_path = "Image-Raw/" + user_id
    os.chdir(dest_path) # directory error check
    os.chdir("../..")

    x = int(start_num)
    base = int(start_num)

    while True:
        filename = str(x) + ".jpg"
    target_filename = "Image-Raw/" + user_id + "/" + filename
    print "Take picture now -- "
        exmod.get_data(filename)
    os.rename("temp.ppm", target_filename)
        print "Image count: %s" % x
        x += 1
    # ctrl-c to exit

if __name__ == "__main__":

    get_rawImgs()
