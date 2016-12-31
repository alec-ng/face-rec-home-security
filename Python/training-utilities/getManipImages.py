###########################################################################
#
#   Author: Alec Ng
#   Brief: Goes into the user directory in Image-Raw, processes each 
#       image and saves it to the mirror user directory in Image-Process, 
#       to be used by gen_traindset.py
#   Requirements: userId dir exists in Image-Raw, Image-Raw subdir 
#       contains >= 1 images, userId dir in Image-Align and
#       Image-Process also exists
#
###########################################################################

import os
import sys
import numpy as np
import imcrop
import cv2
from PIL import Image
import sizeToFace 

# crops, applies grayscale and elliptical mask and CLAHE histogram equalization
# to a given image
def preprocess(raw_img):
    # rotate around eyes, crop, and resize iamge
    # Params: Leye, Reye, Offset_Pct, Dest_size
    raw_img = imcrop.CropFace(raw_img, (80,125), (160,125), (0.32,0.32), (100,100))
    
    # temporarily save
    raw_img.save("temp_process.jpg")
    
    # reopen image as a numpy array and in grayscale mode
    raw2Img = cv2.imread("temp_process.jpg", cv2.IMREAD_GRAYSCALE)

    # create mask image same shape as input image, filled with black
    mask = np.zeros_like(raw2Img)
    rows, cols = mask.shape

    # create white filled ellipse
    mask = cv2.ellipse(mask, center=(rows/2, cols/2), axes=(39,50), angle=0,  startAngle=0, 
        endAngle=360, color=(255,255,255), thickness=-1)

    # bitwise AND to black out regions outside the mask
    raw2Img = np.bitwise_and(raw2Img,mask)

    # create a CLAHE object for adaptive histogram equalization to 
    # improve contrast
    clahe = cv2.createCLAHE(clipLimit=3.0, tileGridSize=(3,3))
    raw2Img = clahe.apply(raw2Img)

    # delete temp copy
    os.remove("temp_process.jpg")

    return raw2Img

def manip_images():
    while True:
        user_id = raw_input("Enter userID (input 1 if done): ")
        if user_id is '1':
            return

        raw_path = "Image-Raw/" + user_id
        process_path = "Image-Process/" + user_id
        align_path = "Image-Align/" + user_id

        # does raw path exist and contain images?
        os.chdir(raw_path)
        numRaw = len([name for name in os.listdir('.') if os.path.isfile(name)])
        if numRaw < 1:
            print "Raw img directory can't be empty.."
            sys.exit()

        # see if a process/align dir exists
        os.chdir("../../" + process_path)
        os.chdir("../../" + align_path)

        # align faces?
        align_choice_raw = raw_input("Enter 1 to align images, 0 to skip: ")
        align_choice = int(align_choice_raw)
        if align_choice == 1:
            sizeToFace.main(user_id)

        # start manipulating all raw images and saving to Image-Process
        for x in range(1, numRaw+1):
            manipName = ""
            os.chdir("../../" + align_path)
            final_filename = str(x) + ".jpg"
        
            processed_img = preprocess(Image.open(final_filename))

            os.chdir("../../" + process_path)

            # save final image
            cv2.imwrite(final_filename, processed_img)
            print "Saved %s" % final_filename
        
        print "Done manipulating and saving images!"
        os.chdir("../..")

if __name__ == "__main__":
    manip_images()
