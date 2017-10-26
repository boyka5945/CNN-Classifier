# encoding=utf-8
import numpy as np
import tensorflow as tf
from PIL import Image
from os import listdir
import shutil
import os
import sys

def img2array(folder):
    List = []
    imglist = listdir(folder)
    imglist.sort(key= lambda x:int(x[:-4]))  
    num = len(imglist)
    for i in range(num):
        path = folder + '/' + imglist[i]
        Img = Image.open(path)
        width = Img.size[0]
        height = Img.size[1]

        if width > height:
            tmp = int((width - height) / 2)
            Img = Img.crop([width - height - tmp, 0, width - tmp, height])
        if height > width:
            tmp = int((height - width) / 2)
            Img = Img.crop([0, height - width - tmp, width, height - tmp])
        size = 32, 32
        Img.thumbnail(size, Image.ANTIALIAS)

        r,g,b = Img.split()
        r_array = np.array(r).reshape([1024])
        g_array = np.array(g).reshape([1024])
        b_array = np.array(b).reshape([1024])

        merge_array = np.concatenate((r_array,g_array,b_array))
        key = { 
            'arr' : merge_array,
            'name' : imglist[i]
        }
        List.append(key)
    return List, num

def weight_variable(shape):
    initial = tf.truncated_normal(shape, stddev=0.01)
    return tf.Variable(initial)


def bias_variable(shape):
    initial = tf.constant(0.01, shape=shape)
    return tf.Variable(initial)


def conv2d(input, in_features, out_features, kernel_size, with_bias=False):
    W = weight_variable([kernel_size, kernel_size, in_features, out_features])
    conv = tf.nn.conv2d(input, W, [1, 1, 1, 1], padding='SAME')
    if with_bias:
        return conv + bias_variable([out_features])
    return conv


def batch_activ_conv(current, in_features, out_features, kernel_size, is_training, keep_prob):
    current = tf.contrib.layers.batch_norm(current, scale=True, is_training=is_training, updates_collections=None)
    current = tf.nn.relu(current)
    current = conv2d(current, in_features, out_features, kernel_size)
    current = tf.nn.dropout(current, keep_prob)
    return current


def block(input, layers, in_features, growth, is_training, keep_prob):
    current = input
    features = in_features
    i = 0
    while i < layers:
        tmp = batch_activ_conv(current, features, growth, 3, is_training, keep_prob)
        current = tf.concat(3, (current, tmp))
        features += growth
        i+=1
    return current, features


def avg_pool(input, s):
    return tf.nn.avg_pool(input, [1, s, s, 1], [1, s, s, 1], 'VALID')


def run_model(image_dim, label_count, depth):
    weight_decay = 1e-4
    layers = (depth - 4) / 3
    dirr = sys.path[0]
    graph = tf.Graph()
    with graph.as_default():
        xs = tf.placeholder("float", shape=[None, image_dim])
        ys = tf.placeholder("float", shape=[None, label_count])
        lr = tf.placeholder("float", shape=[])
        keep_prob = tf.placeholder(tf.float32)
        is_training = tf.placeholder("bool", shape=[])

        current = tf.reshape(xs, [-1, 32, 32, 3])
        current = conv2d(current, 3, 16, 3)

        current, features = block(current, layers, 16, 12, is_training, keep_prob)
        current = batch_activ_conv(current, features, features, 1, is_training, keep_prob)
        current = avg_pool(current, 2)
        current, features = block(current, layers, features, 12, is_training, keep_prob)
        current = batch_activ_conv(current, features, features, 1, is_training, keep_prob)
        current = avg_pool(current, 2)
        current, features = block(current, layers, features, 12, is_training, keep_prob)

        current = tf.contrib.layers.batch_norm(current, scale=True, is_training=is_training, updates_collections=None)
        current = tf.nn.relu(current)
        current = avg_pool(current, 8)
        final_dim = features
        current = tf.reshape(current, [-1, final_dim])
        Wfc = weight_variable([final_dim, label_count])
        bfc = bias_variable([label_count])
        ys_ = tf.nn.softmax(tf.matmul(current, Wfc) + bfc)

    with tf.Session(graph=graph) as session:
        session.run(tf.global_variables_initializer())
        saver = tf.train.Saver()
        saver.restore(session, dirr + '/densenet_300.ckpt')
        arr, num = img2array(dirr + '/SpiderData')
        for i in range(0,num):
            arr1 = arr[i]['arr'].reshape((-1, 3, 32, 32)).swapaxes(1, 3).swapaxes(1, 2).reshape(-1, 32*32*3) / 256.
            prediction = tf.argmax(ys_,1)
            prediction = prediction.eval(feed_dict={xs: arr1, is_training: False,keep_prob: 1.0}, session=session) 
            print ('第' + str(i + 1) + '张图片是：')
            if prediction[0] == 0:
                shutil.move(dirr + '/SpiderData/' + arr[i]['name'], dirr + '/pictureData/airplain/')
                print('飞机')
            elif prediction[0] == 1:
                shutil.move(dirr + '/SpiderData/' + arr[i]['name'], dirr + '/pictureData/car/')
                print('小汽车')
            elif prediction[0] == 2:
                shutil.move(dirr + '/SpiderData/' + arr[i]['name'], dirr + '/pictureData/bird/')
                print('鸟')
            elif prediction[0] == 3:
                shutil.move(dirr + '/SpiderData/' + arr[i]['name'], dirr + '/pictureData/cat/')
                print('猫')
            elif prediction[0] == 4:
                shutil.move(dirr + '/SpiderData/' + arr[i]['name'], dirr + '/pictureData/deer/')
                print('鹿')
            elif prediction[0] == 5:
                shutil.move(dirr + '/SpiderData/' + arr[i]['name'], dirr + '/pictureData/dog/')
                print('狗')
            elif prediction[0] == 6:
                shutil.move(dirr + '/SpiderData/' + arr[i]['name'], dirr + '/pictureData/frog/')
                print('青蛙')
            elif prediction[0] == 7:
                shutil.move(dirr + '/SpiderData/' + arr[i]['name'], dirr + '/pictureData/horse/')
                print('马')
            elif prediction[0] == 8:
                shutil.move(dirr + '/SpiderData/' + arr[i]['name'], dirr + '/pictureData/boat/')
                print('船')
            elif prediction[0] == 9:
                shutil.move(dirr + '/SpiderData/' + arr[i]['name'], dirr + '/pictureData/trunk/')
                print('大卡车')

def run():
    image_dim = 32 * 32 * 3

    label_count = 10

    run_model(image_dim, label_count, 40)


run()
