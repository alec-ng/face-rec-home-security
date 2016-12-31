###########################################################################
#
#   All credits go to roblourens: https://github.com/roblourens/facealign
#
###########################################################################

#!/usr/bin/python
 
# Face Detection using OpenCV
 
# Usage: python sizeToFace.py <image_directory> optional: <output_directory> <start_num>,<end_num>
# ffmpeg -r 15 -b 1800 -i %4d.JPG -i testSong.mp3 test1800.avi
 
import FaceImage
from multiprocessing import Pool
import sys, os
from operator import itemgetter
from PIL import Image

def align_single(img_path):
    test_pic = img_path
    out_dir ='/home/pi/Desktop/Home-Security/Python/face_rec/temp'
    lab = 1

    # Get input files, sort by last modified time
    files = (test_pic,lab)

    if len(files) == 0:
        print('No test.jpg in temp dir')
        return

    outdir = out_dir

    start, end = 0, len(files)-1
   
    files = files[start:end+1]
    i=start

    filepath = test_pic
    savename = '/home/pi/Desktop/Home-Security/Python/face_rec/temp/1.jpg'

    print('Added to pool: ' + filepath + ' with output path: ' + savename)
    FaceImage.runFaceImage(filepath, savename)



def main(user_id):
    raw_dir = '/home/pi/Desktop/Home-Security/Python/face_rec/recognizer_generator/Image-Raw/' + user_id
    align_dir ='/home/pi/Desktop/Home-Security/Python/face_rec/recognizer_generator/Image-Align/' + user_id

    # Get input files, sort by last modified time
    files = sortedImages(raw_dir)

    if len(files) == 0:
        print('No jpg files found in ' + raw_dir)
        return

    outdir = align_dir

    start, end = 0, len(files)-1
   
    files = files[start:end+1]
    i=start
    pool = Pool()

    # For every JPG in the given directory
    for file in files:
        filepath = file[1]
        i += 1
        savename = os.path.join(outdir, '%d.jpg' % i)

        print('Added to pool: ' + filepath + ' with output path: ' + savename)
        pool.apply_async(FaceImage.runFaceImage, (filepath, savename))

    pool.close()
    pool.join()

def sortedImages(inputDir):
    files = []
    i = 0
    for dirpath, dirnames, filenames in os.walk(inputDir):
        for filename in filenames:
            filePath = os.path.join(dirpath, filename)
            files.append((i, filePath))
            i+=1

    # Sort by last modified, then by path
    # (some old pics in my set have an equal recent modified time)
    files.sort(key=itemgetter(0,1))
    return files

def getImageDate(filePath):
    """ This returns the date as a formatted string like yyyy:mm:dd hh:mm:ss. Which is good enough for sorting. """
    DateTimeOriginalKey = 36867
    print filePath;
    return Image.open(filePath)._getexif()[DateTimeOriginalKey]
