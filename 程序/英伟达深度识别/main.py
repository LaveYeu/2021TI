import numpy as np
import cv2 as cv
import torch
import torch.nn as nn   # 包括卷积参，激活参，池化层，全连接层
import torch.nn.functional as F
import RPi.GPIO as GPIO
import time


IMAGE_WIDTH = 28
IMAGE_HEIGHT = 28
images = []
labels = []
RESIZE_IMG_PATH = "/home/jetson/Desktop/number/nnnn/"

counter = 0

def erode_demo(image):
    kernel = cv.getStructuringElement(cv.MORPH_RECT, (4, 4))#定义结构元素的形状和大小
    dst = cv.erode(image, kernel)#腐蚀操作
    return dst

def dilate_demo(image):
    kernel = cv.getStructuringElement(cv.MORPH_RECT, (18, 18))#定义结构元素的形状和大小
    dst = cv.dilate(image, kernel)#膨胀操作
    return dst

# 根据设定的阈值和图片直方图，找出波峰，用于分隔字符
def find_waves(threshold, histogram):
    up_point = -1  # 上升点
    is_peak = False
    if histogram[0] > threshold:
        up_point = 0
        is_peak = True
    wave_peaks = []
    for i, x in enumerate(histogram):
        if is_peak and x < threshold:
            if i - up_point > 2:
                is_peak = False
                wave_peaks.append((up_point, i))
        elif not is_peak and x >= threshold:
            is_peak = True
            up_point = i
    if is_peak and up_point != -1 and i - up_point > 4:
        wave_peaks.append((up_point, i))
    return wave_peaks

def remove_plate_upanddown_border(card_img):
    """
    这个函数将截取到的车牌照片转化为灰度图，然后去除车牌的上下无用的边缘部分，确定上下边框
    输入： card_img是从原始图片中分割出的车牌照片
    输出: 在高度上缩小后的字符二值图片
    """
    plate_Arr = card_img
    # print(plate_Arr)
    row_histogram = np.sum(plate_Arr, axis=1)  # 数组的每一行求和
    row_min = np.min(row_histogram)
    row_average = np.sum(row_histogram) / plate_Arr.shape[0]
    row_threshold = (row_min + row_average) / 2
    wave_peaks = find_waves(row_threshold, row_histogram)
    # 接下来挑选跨度最大的波峰
    wave_span = 0.0
    for wave_peak in wave_peaks:
        span = wave_peak[1] - wave_peak[0]
        if span > wave_span:
            wave_span = span
            selected_wave = wave_peak
    plate_binary_img = plate_Arr[selected_wave[0]:selected_wave[1], :]
    plate_binary_img = erode_demo(plate_binary_img)
    # cv.imshow("plate_binary_img", plate_binary_img)

    return plate_binary_img

#####################二分-K均值聚类算法############################

def distEclud(vecA, vecB):
    """
    计算两个坐标向量之间的街区距离
    """
    return np.sum(abs(vecA - vecB))

def randCent(dataSet, k):
    n = dataSet.shape[1]  # 列数
    centroids = np.zeros((k, n))  # 用来保存k个类的质心
    for j in range(n):
        minJ = np.min(dataSet[:, j], axis=0)
        rangeJ = float(np.max(dataSet[:, j])) - minJ
        for i in range(k):
            centroids[i:, j] = minJ + rangeJ * (i + 1) / k
    return centroids

def kMeans(dataSet, k, distMeas=distEclud, createCent=randCent):
    m = dataSet.shape[0]
    clusterAssment = np.zeros((m, 2))  # 这个簇分配结果矩阵包含两列，一列记录簇索引值，第二列存储误差。这里的误差是指当前点到簇质心的街区距离
    centroids = createCent(dataSet, k)
    clusterChanged = True
    while clusterChanged:
        clusterChanged = False
        for i in range(m):
            minDist = np.inf
            minIndex = -1
            for j in range(k):
                distJI = distMeas(centroids[j, :], dataSet[i, :])
                if distJI < minDist:
                    minDist = distJI
                    minIndex = j
            if clusterAssment[i, 0] != minIndex:
                clusterChanged = True
            clusterAssment[i, :] = minIndex, minDist ** 2
        for cent in range(k):
            ptsInClust = dataSet[np.nonzero(clusterAssment[:, 0] == cent)[0]]
            centroids[cent, :] = np.mean(ptsInClust, axis=0)
    return centroids, clusterAssment

def biKmeans(dataSet, k, distMeas=distEclud):
    """
    这个函数首先将所有点作为一个簇，然后将该簇一分为二。之后选择其中一个簇继续进行划分，选择哪一个簇进行划分取决于对其划分是否可以最大程度降低SSE的值。
    输入：dataSet是一个ndarray形式的输入数据集
          k是用户指定的聚类后的簇的数目
         distMeas是距离计算函数
    输出:  centList是一个包含类质心的列表，其中有k个元素，每个元素是一个元组形式的质心坐标
            clusterAssment是一个数组，第一列对应输入数据集中的每一行样本属于哪个簇，第二列是该样本点与所属簇质心的距离
    """
    m = dataSet.shape[0]
    clusterAssment = np.zeros((m, 2))
    centroid0 = np.mean(dataSet, axis=0).tolist()
    centList = []
    centList.append(centroid0)
    for j in range(m):
        clusterAssment[j, 1] = distMeas(np.array(centroid0), dataSet[j, :]) ** 2
    while len(centList) < k:  # 小于K个簇时
        lowestSSE = np.inf
        for i in range(len(centList)):
            ptsInCurrCluster = dataSet[np.nonzero(clusterAssment[:, 0] == i)[0], :]
            centroidMat, splitClustAss = kMeans(ptsInCurrCluster, 2, distMeas)
            sseSplit = np.sum(splitClustAss[:, 1])
            sseNotSplit = np.sum(clusterAssment[np.nonzero(clusterAssment[:, 0] != i), 1])
            if (sseSplit + sseNotSplit) < lowestSSE:  # 如果满足，则保存本次划分
                bestCentTosplit = i
                bestNewCents = centroidMat
                bestClustAss = splitClustAss.copy()
                lowestSSE = sseSplit + sseNotSplit
        bestClustAss[np.nonzero(bestClustAss[:, 0] == 1)[0], 0] = len(centList)
        bestClustAss[np.nonzero(bestClustAss[:, 0] == 0)[0], 0] = bestCentTosplit
        centList[bestCentTosplit] = bestNewCents[0, :].tolist()
        centList.append(bestNewCents[1, :].tolist())
        clusterAssment[np.nonzero(clusterAssment[:, 0] == bestCentTosplit)[0], :] = bestClustAss
    return centList, clusterAssment

def split_licensePlate_character(plate_binary_img):
    """
    此函数用来对车牌的二值图进行水平方向的切分，将字符分割出来
    输入： plate_gray_Arr是车牌的二值图，rows * cols的数组形式
    输出： character_list是由分割后的车牌单个字符图像二值图矩阵组成的列表
    """
    plate_binary_Arr = np.array(plate_binary_img)
    row_list, col_list = np.nonzero(plate_binary_Arr >= 255)
    dataArr = np.column_stack((col_list, row_list))  # dataArr的第一列是列索引，第二列是行索引，要注意
    centroids, clusterAssment = biKmeans(dataArr, 1, distMeas=distEclud)
    centroids_sorted = sorted(centroids, key=lambda centroid: centroid[0])
    split_list = []
    for centroids_ in centroids_sorted:
        i = centroids.index(centroids_)
        current_class = dataArr[np.nonzero(clusterAssment[:, 0] == i)[0], :]
        x_min, y_min = np.min(current_class, axis=0)
        x_max, y_max = np.max(current_class, axis=0)
        split_list.append([y_min, y_max, x_min, x_max])
    character_list = []
    for i in range(len(split_list)):
        single_character_Arr = plate_binary_img[split_list[i][0]: split_list[i][1], split_list[i][2]:split_list[i][3]]
        character_list.append(single_character_Arr)
        img11 = single_character_Arr
    return img11 # character_list中保存着每个字符的二值图数据

def resize_image(image, height = IMAGE_HEIGHT, width = IMAGE_WIDTH):
    top, botton, left, right = 0, 0, 0, 0
    h, w= image.shape
    loggest_edge = max(h, w)

    # 计算短边需要多少增加多少宽度使之长宽相等
    if h < loggest_edge:
        dh = loggest_edge - h
        top = dh // 2
        botton = dh - top
    elif w < loggest_edge:
        dw = loggest_edge - w
        left = dw // 2
        right = dw - left
    else:
        pass

    BLACK = [0]
    # 将图像转换为一个正方形的image，两边或者上下缺少的的用黑色矩形填充
    constant = cv.copyMakeBorder(image, top+2, botton+2, left+2, right+2, cv.BORDER_CONSTANT, value=BLACK)
    return cv.resize(constant, (height, width))


torch.manual_seed(1)    # reproducible
class Net(nn.Module):
    def __init__(self):
         #nn.Module子类的函数必须在构造函数中执行父类的构造函数
        super(Net, self).__init__()
        self.conv1 = nn.Conv2d(1, 6, 5)
        self.pool = nn.MaxPool2d(2, 2)
        self.conv2 = nn.Conv2d(6, 16, 5)
        self.fc1 = nn.Linear(256, 120) # 全连接层输入是16*5*5的，输出是120的
        self.fc2 = nn.Linear(120, 64)
        self.fc3 = nn.Linear(64, 9) # 定义输出为10，因为10各类
    def forward(self, x):
        batch_size = x.size(0)
        x =self.pool(F.relu(self.conv1(x)))  # 输入x经过卷积conv1之后，经过激活函数ReLU，然后更新到x。
        x =self.pool(F.relu(self.conv2(x)))
        # x = x.view(-1, 256) #用来将x展平成16 * 5 * 5，然后就可以进行下面的全连接层操作
        x = x.view(batch_size, -1)
        x = F.relu(self.fc1(x))# 输入x经过全连接1，再经过ReLU激活函数，然后更新x
        x = F.relu(self.fc2(x))# 输入x经过全连接2，再经过ReLU激活函数，然后更新x
        x =self.fc3(x) # 输入x经过全连接3，然后更新x
        return x
cnn = torch.load('/home/jetson/Desktop/number/numberCnn50.pth')

pred_y1 = [0]
pred_y2 = [0]
pred_y3 = [0]
GPIO.setmode(GPIO.BCM)
GPIO.setup(17, GPIO.IN)
GPIO.setup(18, GPIO.IN)
GPIO.setup(27, GPIO.OUT, initial=0)#15
GPIO.setup(22, GPIO.OUT, initial=0)#13
GPIO.setup(10, GPIO.OUT, initial=0)#19

while(1):
    if (GPIO.input(17) == 0):
        cap = cv.VideoCapture(0)
        cap.set(3, 320)
        cap.set(4, 240)
        while cap.isOpened():
            ret, frame = cap.read()
            '''****************************************8'''
            counter = counter + 1
            stt1 = RESIZE_IMG_PATH+"78_" + str(counter)+".jpg"
            cv.imwrite(stt1, frame)
            '''*****************************************'''
            # print(stt1)
            #cv.imshow("frame", frame)
            if (counter == 5):
                break
            key = cv.waitKey(1)
            if key == 27:  # esc 按键
                break
        cap.release()
        cv.destroyAllWindows()
        print("照片拍摄完成")
        GPIO.output(10, 1)

        stt1 = RESIZE_IMG_PATH + "78_" + str(3) + ".jpg"
        img = cv.imread(stt1)

        gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
        retval, dst = cv.threshold(gray, 55, 255, cv.THRESH_BINARY_INV)
        dst1 = remove_plate_upanddown_border(dst)
        dimg1 = split_licensePlate_character(dst1)
        dimg1 = resize_image(dimg1)
        key = cv.waitKey(1)
        b = torch.Tensor(dimg1)
        b = torch.unsqueeze(b, dim=0)
        b = torch.unsqueeze(b, dim=0)
        test_output = cnn(b)
        pred_y1[0] = int(torch.max(test_output, 1)[1].data.numpy().squeeze())

        GPIO.output(10, 0)
        print("识别完成")
        print(pred_y1[0])
        if (pred_y1[0] == 2):
            GPIO.output(27, 1)
        else:
            GPIO.output(22, 1)
        counter = 0
        while(GPIO.input(18) == 0):
            pass
        break
pred_y1[0] = 0
while(1):
    if (GPIO.input(17) == 0):
        cap = cv.VideoCapture(0)
        cap.set(3, 320)
        cap.set(4, 240)
        while cap.isOpened():
            ret, frame = cap.read()
            '''****************************************8'''
            counter = counter + 1
            stt1 = RESIZE_IMG_PATH+"78_" + str(counter)+".jpg"
            cv.imwrite(stt1, frame)
            '''*****************************************'''
            if (counter == 5):
                break
            key = cv.waitKey(1)
            if key == 27:  # esc 按键
                break
        cap.release()
        cv.destroyAllWindows()
        print("照片拍摄完成2")
        GPIO.output(10, 1)

        stt1 = RESIZE_IMG_PATH + "78_" + str(3) + ".jpg"
        img = cv.imread(stt1)

        gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
        retval, dst = cv.threshold(gray, 55, 255, cv.THRESH_BINARY_INV)
        dst1 = remove_plate_upanddown_border(dst)
        dimg1 = split_licensePlate_character(dst1)
        dimg1 = resize_image(dimg1)
        key = cv.waitKey(1)
        b = torch.Tensor(dimg1)
        b = torch.unsqueeze(b, dim=0)
        b = torch.unsqueeze(b, dim=0)
        test_output = cnn(b)
        pred_y1[0] = int(torch.max(test_output, 1)[1].data.numpy().squeeze())

        GPIO.output(10, 0)
        print("识别完成")
        print(pred_y1[0])
        
        while(GPIO.input(18) == 0):
            pass

        counter = 0

        cap = cv.VideoCapture(0)
        cap.set(3, 320)
        cap.set(4, 240)

        while cap.isOpened():
            ret, frame = cap.read()
            '''****************************************8'''
            counter = counter + 1
            stt1 = RESIZE_IMG_PATH+"78_" + str(counter)+".jpg"
            cv.imwrite(stt1, frame)
            '''*****************************************'''
            if (counter == 5):
                break
            key = cv.waitKey(1)
            if key == 27:  # esc 按键
                break
        cap.release()
        cv.destroyAllWindows()
        print("照片拍摄完成3")
        stt1 = RESIZE_IMG_PATH + "78_" + str(3) + ".jpg"
        img = cv.imread(stt1)

        gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
        retval, dst = cv.threshold(gray, 55, 255, cv.THRESH_BINARY_INV)
        dst1 = remove_plate_upanddown_border(dst)
        dimg1 = split_licensePlate_character(dst1)
        dimg1 = resize_image(dimg1)
        key = cv.waitKey(1)
        b = torch.Tensor(dimg1)
        b = torch.unsqueeze(b, dim=0)
        b = torch.unsqueeze(b, dim=0)
        test_output = cnn(b)
        pred_y2[0] = int(torch.max(test_output, 1)[1].data.numpy().squeeze())
        print("识别完成后")
        print(pred_y2[0])
        if (pred_y1[0] == pred_y2[0]):
            GPIO.output(22, 1)
        else:
            GPIO.output(27, 1)
        counter = 0
        while(GPIO.input(18) == 0):
            pass
        break
time.sleep(10)
