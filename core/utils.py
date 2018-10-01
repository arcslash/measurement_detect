'''utils module will handle everything from file operations,convertions,image resizing and producing the dataset in the trainable format'''

from os import listdir
from os.path import isfile, join
import json
from PIL import Image
import numpy as np
import matplotlib as mpl
mpl.use('Agg')
import matplotlib.pyplot as plt






#variables requred in image processing
image_resize = (96, 96)

'''
Loades up images and lables and returns up the vector required to be fed into the neural network
Requirements:
    *labelme or compatible labeled dataset with json files
'''
def load_dataset():
    dataset_folder = "core/data/"
    train_folder = "core/data/"
    test_folder = "core/data/"

    x_train = []
    y_train = []
    x_test = []
    y_test = []
    json_list = []
    isTest = False
    json_list_train = [f for f in listdir(train_folder) if(isfile(join(train_folder, f))) if(".json" in f)]
    json_list_test = [f for f in listdir(test_folder) if (isfile(join(test_folder, f))) if (".json" in f)]
    json_list.append(json_list_train)
    json_list.append(json_list_test)
    for type in json_list:
        for file in type:
            if(not isTest):
                data = json.load(open(join(train_folder, file)))
                jpgfile = data["imagePath"]
                img = Image.open(join(train_folder, jpgfile))
            else:
                data = json.load(open(join(test_folder, file)))
                jpgfile = data["imagePath"]
                img = Image.open(join(test_folder, jpgfile))
            labellist = data["points"]
            print(labellist)
            for i in range(len(labellist)):
                labellist[i][0] = float(labellist[i][0]) * float(image_resize[0] / img.size[0])
                labellist[i][1] = float(labellist[i][1]) * float(image_resize[1] / img.size[1])
            y = np.array(labellist)
            y = y.reshape(y.shape[0] * y.shape[1])
            x = np.vstack([img.convert('L').resize(image_resize, Image.ANTIALIAS)]) / 255.
            x = x.astype(np.float32)
            x = x.reshape(image_resize[0], image_resize[1], 1)
            if (not isTest):
                x_train.append(x)
                y_train.append(y)
            else:
                x_test.append(x)
                y_test.append(y)
        isTest = True
    x_train = np.array(x_train)
    y_train = np.array(y_train)
    x_test = np.array(x_test)
    y_test = np.array(y_test)
    print("Shape X Train:{}".format(x_train.shape))
    print("Shape Y Train:{}".format(y_train.shape))
    print("Shape X Test:{}".format(x_test.shape))
    print("Shape Y Test:{}".format(y_test.shape))

    return x_train, y_train, x_test, y_test


'''

'''
def label_to_original(label, filepath):
    img = Image.open(filepath)
    for l in label:
        for a in range(0,len(l),2):
            l[a] = float(l[a]) * float(img.size[0] / image_resize[0])
            l[a+1] = float(l[a+1]) * float(img.size[1] / image_resize[1])

    img = np.expand_dims(img, axis=0)
    return img, label

def label_to_original_seg(label, filepath):
    img = Image.open(filepath)
    for l in label:
        l[0] = float(l[0]) * float(img.size[0] / image_resize[0])
        l[1] = float(l[1]) * float(img.size[1] / image_resize[1])
        l[2] = float(l[2]) * float(img.size[0] / image_resize[0])
        l[3] = float(l[3]) * float(img.size[1] / image_resize[1])

    img = np.expand_dims(img, axis=0)
    return img, label

def plot_data(img, landmarks, axis):
    """
    Plot image (img), along with normalized facial keypoints (landmarks)
    """
    axis.imshow(np.squeeze(img), cmap='gray') # plot the image
    #landmarks = landmarks * 48 + 48 # undo the normalization
    # Plot the keypoints
    axis.scatter(landmarks[0::2], landmarks[1::2], marker='o', c='c', s=40)
def row_to_coordinates(co_row):
    #print((int(co_row.shape[0]/2), 2))
    points = np.zeros((6, 2))
    for i in range(co_row.shape[0]):
        points[int(i/2)][i % 2]
    return points

def display(x,y, filename):
    fig = plt.figure(figsize=(20, 20))
    fig.subplots_adjust(left=0, right=1, bottom=0, top=1, hspace=0.05, wspace=0.05)
    ax = fig.add_subplot(1, 1, 1, xticks=[], yticks=[])
    plot_data(x[0], y[0], ax)
    fig.savefig(filename)
    print("[+]Saving final image...{}".format(filename))

def load_image_resized(path):
    img = Image.open(path)
    x = np.vstack([img.convert('L').resize(image_resize, Image.ANTIALIAS)]) / 255.
    x = x.astype(np.float32)
    x = x.reshape(1, image_resize[0], image_resize[1], 1)
    return x
