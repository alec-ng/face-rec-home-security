###########################################################################
#
#   Author: Alec Ng
#   Brief: creates a new user in system, in that a new user ID is 
#       assigned, the user is asked to take at least one picture,
#       the pictures are processed and the fisher model is retrained
#   Requires: root access for GPIO communication
#
###########################################################################

import os
import sys
import numpy as np
from getRawImgs import new_user_rawImgs
from getManipImages import manip_images
from gen_trainedSet import gen_fisherface_set

def create_User():

    checkDir = False

    while checkDir is False:
        user_id = raw_input("Enter a new user ID to assign to yourself: ")

        raw_user_dir = "Image-Raw/" + user_id
        align_user_dir = "Image-Align/" + user_id
        process_user_dir = "Image-Process/" + user_id

        if os.path.isdir(raw_user_dir) is True or os.path.isdir(align_user_dir) is True or os.path.isdir(process_user_dir) is True:
            print "User already exists, try again"
            continue

        print "Creating directories..."
        checkDir = True
        os.mkdir(raw_user_dir)
        os.mkdir(align_user_dir)
        os.mkdir(process_user_dir)

    new_user_rawImgs(user_id)
    print "Now preprocessing images... "
    manip_images()
    print "Now training the set..."
    gen_fisherface_set()
    print "New user successfully added into system"

if __name__ == "__main__":

    create_User()
