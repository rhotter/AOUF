from PIL import Image
import os

orig_dir = 'training_images/'

file_dirs = [orig_dir+f for f in os.listdir(orig_dir) if '.jpeg' in f]

for file in file_dirs:
    old_im = Image.open(file)
    old_size = old_im.size

    new_size = (640, 448)
    new_im = Image.new("RGB", new_size)   ## luckily, this is already black!
    new_im.paste(old_im, (int((new_size[0]-old_size[0])/2),
                          int((new_size[1]-old_size[1])/2)))
    new_im.save(file)
