###########################################################################
#
#   Author: Alec Ng
#   Brief: Generates an xml file which corresponds to a trained 
#       FisherFace set. Reads all images in Image-Process and assigns 
#       a label (person identifier) corresponding to the subdirectory
#       name (which should be the user ID)
#   Requires: At least two users with images in their respective
#       Image-Process direectoies
#
###########################################################################

import os
import cv2
import sys
import numpy as np
from PIL import Image

# takes a path to a folder with subfolders representing the subjects (persons)
# returns a list [X,y], X=images, as Python list of numpy arrys and y, the corresponding
# label (unique number of the user) in a Python list
def read_images(path, sz=None):

    c = 0
    X,y = [], []

    # walk() generates file names in a directory tree by walking the the tree top-bottom
    # or bottom-up
    # each directory rooted at directory yields 3-tuples (dirname, dirnames, filenames)
    for dirname, dirnames, filenames in os.walk(path):
        for subdirname in dirnames:
            subject_path = os.path.join(dirname, subdirname) 
        # os.listdir() returns a list containing the names of the entries in the directory given
            # by path
            for filename in os.listdir(subject_path):
                try:
                    im = Image.open(os.path.join(subject_path, filename))
                    X.append(np.asarray(im, dtype=np.uint8))
                    # label is the unique ID of the subject (specified by the subdirname)
                    y.append(subdirname)
                except IOError, (errno, strerror):
                    print "I/O error({0}): {1}".format(errno, strerror)
                except:
                    print "Unexpected error:", sys.exc_info()[0]
                    raise
            c = c+1
    return [X,y]

def gen_fisherface_set():
    
    # read the image data and store in an aray
    [X,y] = read_images("Image-Process")

    # convert labels to 32 bit ints (workaround for 64bit machines)
    y = np.asarray(y, dtype=np.int32)

    # create the fisherface model object
    model = cv2.face.createFisherFaceRecognizer()

    # tell user which users will be trained
    print "Training a set with these user IDs: "
    print np.asarray(y)

    print "Training the FisherFace model. This could take a while.."
    model.train(np.asarray(X), np.asarray(y))

    # save the model in main parent dictory for main.py
    print "Trained successfully. Saving .xml file - this will take a long time..."
    os.chdir('..')
    model.save("trainedFisherModel.xml")
    print "Face successfully trained and saved."

if __name__ == "__main__":

    gen_fisherface_set()
