import numpy as np
# import scipy
from PIL import Image
import matplotlib.pyplot as plt
import matplotlib.image as img
import math
import sys

im = Image.open(sys.argv[1])
im_array = im.load()
print(im_array)

width = 640
height = 448
segmented = np.zeros((4,4))

for h in range(height -1 ):
    for w in range(width -1):
        dif1 = np.linalg.norm(np.array(im_array[w,h]) - np.array([146,142,89]))
        dif2 = np.linalg.norm(np.array(im_array[w,h]) - np.array([151,149,122]))
        if min(dif1, dif2) < 5:
            segmented[math.floor(h/height*4), math.floor(w/width*4)] += 1
        # print(im_array[h, w, :])
max = segmented.max()
segmented = segmented == max

im_plot = plt.imshow(segmented)
plt.show(im_plot)
