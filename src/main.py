from PIL import Image
import numpy as np
import pprint

input_datafile = "../input/image_info.dat"

im = Image.open('../input/lenna_test_image.png')

dim = np.array(im.size)
pixels = np.array(im.getdata())

with open(input_datafile, 'w'): pass # Emptying the file first
with open(input_datafile, "ba") as file: # Sending dimensions and pixel data to dat file for C program input 
    np.savetxt(file,dim.astype(int), fmt="%i")
    np.savetxt(file,pixels.astype(int), fmt="%i")

# pprint.pprint(pixels)

# im.save('../output/output.png')