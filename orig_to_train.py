# encoding: utf-8
import os 

orig_dir = 'orig/'
to_dir = 'training_data/'
img_dir = 'training_images/'

file_dirs = [orig_dir+f for f in os.listdir(orig_dir) if '.txt' in f]
img_dirs = [img_dir+f for f in os.listdir(img_dir) if '.jpeg' in f]

write_f = open(to_dir + 'train.txt', 'w+')
# print(file_dirs[1][len(orig_dir):-4]+'.jpeg')
# print(file_dirs)
index =0
for fdir in file_dirs:
    with open(fdir, 'r') as read_f:
        # text = f.read()
        # print(text)
        c = 0
        to_write = '../'+img_dir+fdir[len(orig_dir):-4]+'.jpeg'
        for line in read_f:
            to_write_line=''
            if c % 2 == 1:
                to_write_line+=' '
                words = line.split(' ')
                words = [word.rstrip() for word in words]
                for word in words:
                    to_write_line+=word+','
                to_write_line+='0'
            to_write+=to_write_line
            c+=1
        write_f.write(to_write+'\n')
    index+=1
write_f.close()