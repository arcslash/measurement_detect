#!/usr/bin/env python
from PIL import Image
import numpy as np
import cv2
import scipy.misc
from subprocess import call
import time
import models
import os.path



needtrain = False
abs_path = os.path.abspath(os.path.dirname(__file__))
def run():
    

    if needtrain:
        x_train, y_train, x_test, y_test = utils.load_dataset()
        models.train_main_model(x_train, y_train)
    x_off = 100
    y_off = 50
    filename = os.path.join(abs_path, "testcalibnew1.jpg")
    y_predict = models.predict_main_model(filename)
    points = y_predict[0]
    img = Image.open(filename)
    im_x,im_y = img.size
    print("Image Size:"+str(im_x) + "," + str(im_y))
    img.save(os.path.join(abs_path, "outputs/original.jpg"))
    threshold = 0.8


    x_off_p = 60
    y_off_p = 60
    print("[+]No of points:",len(points)/2)
    file = open(os.path.join(abs_path, "outputs/areas.txt"),"w")
    file.write(str(1) +  '\n')
    file.close()
    for i in range(0,len(points),2):
        x_top = points[i] - x_off_p if (points[i] - x_off_p > 0) else 0
        y_top = points[i+1] - y_off_p if (points[i+1] - y_off_p > 0) else 0
        x_down = points[i] + x_off_p if (points[i] + x_off_p < im_x) else im_x
        y_down = points[i+1] + y_off_p if (points[i+1] + y_off_p < im_y) else im_y

        area = (x_top, y_top, x_down , y_down )
        print("Area:"+str(int(i/2)),area)
        cropped_img = np.array(img.crop(area).convert('L'))
        scipy.misc.imsave(os.path.join(abs_path, "outputs/cropped_" + str(int(i/2)) + ".jpg"), cropped_img)
        file = open(os.path.join(abs_path,"outputs/areas.txt"),"a")
        # file.write(str(area) + '\n')
        file.write(str(area[0]) +'\n' + str(area[1]) + '\n')
        file.close()

    print("[+]Running Nihals code")
    call(["pwd"])
    call(["cmake","core/build"])
    call(["make"])
    call(["./corner","core/"])
    call(["./kitty"])


if __name__ == '__main__':
    print("[+]Running individually as the main module")
    run()
    
    #print(abs_path)
