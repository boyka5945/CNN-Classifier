# -*- coding: utf-8 -*-
import requests
import os
from PIL import Image
import sys
import urllib
from os import listdir

def getManyPages(keyword,pages):
    params=[]
    for i in range(30,30*pages+1,1):
        params.append({
                      'tn': 'resultjson_com',
                      'ipn': 'rj',
                      'ct': 201326592,
                      'is': '',
                      'fp': 'result',
                      'queryWord': keyword,
                      'cl': 2,
                      'lm': -1,
                      'ie': 'utf-8',
                      'oe': 'utf-8',
                      'adpicid': '',
                      'st': -1,
                      'z': '',
                      'ic': 0,
                      'word': keyword,
                      's': '',
                      'se': '',
                      'tab': '',
                      'width': '',
                      'height': '',
                      'face': 0,
                      'istype': 2,
                      'qc': '',
                      'nc': 1,
                      'fr': '',
                      'pn': i,
                      'rn': 10,
                      'gsm': '1e',
                      '1488942260214': ''
                  })
    url = 'https://image.baidu.com/search/acjson'
    urls = []
    for i in params:
        urls.append(requests.get(url,params=i).json().get('data'))

    return urls


def getImg(dataList, localPath):

    if not os.path.exists(localPath): 
        os.mkdir(localPath)
    imglist = listdir(localPath);
    num = len(imglist)
    x = num
    for list in dataList:
        for i in list:
            if i.get('thumbURL') != None:
                print('Downloading %s' % i.get('thumbURL'))
                ir = requests.get(i.get('thumbURL'))
                open(localPath + '%d.jpg' % (x), 'wb').write(ir.content)
                f = Image.open(localPath + '%d.jpg' % (x))
                if f.mode == 'RGB':
                  x += 1
                f.close()
            else:
                print('is not exsit')

if __name__ == '__main__':
 
    name = sys.argv[1]
    number = sys.argv[2]
    if name == 'cat':
      dataList = getManyPages('猫', int(number[0]))
    elif name == 'dog':
      dataList = getManyPages('狗', int(number[0]))
    elif name == 'deer':
      dataList = getManyPages('鹿', int(number[0]))
    elif name == 'frog':
      dataList = getManyPages('青蛙', int(number[0]))
    elif name == 'airplain':
      dataList = getManyPages('飞机', int(number[0]))
    elif name == 'boat':
      dataList = getManyPages('船', int(number[0]))
    elif name == 'trunk':
      dataList = getManyPages('卡车', int(number[0]))
    elif name == 'horse':
      dataList = getManyPages('马', int(number[0]))
    elif name == 'car':
      dataList = getManyPages('轿车', int(number[0]))
    elif name == 'bird':
      dataList = getManyPages('鸟', int(number[0]))
    dir = sys.path[0]
    getImg(dataList, dir + '/SpiderData/') 
