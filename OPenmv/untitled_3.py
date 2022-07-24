import pyb, sensor, image, math, time
from pyb import UART
import ustruct
from image import SEARCH_EX, SEARCH_DS
from pyb import LED
#传感器配置

sensor.set_contrast(1)
sensor.set_gainceiling(16)

#可以通过设置窗口来减少搜索的图像
#sensor.set_windowing(((640-80)//2, (480-60)//2, 80, 60))

clock = time.clock()
p2=pyb.Pin("P2",pyb.Pin.OUT_PP)
p3=pyb.Pin("P3",pyb.Pin.OUT_PP)
p4=pyb.Pin("P4",pyb.Pin.OUT_PP)
p5=pyb.Pin("P5",pyb.Pin.OUT_PP)
p6=pyb.Pin("P6",pyb.Pin.OUT_PP)
p7=pyb.Pin("P7",pyb.Pin.OUT_PP)

p8=pyb.Pin("P8",pyb.Pin.OUT_PP)

p2.low()
p3.low()
p4.low()
p5.low()
p6.low()
p7.low()
p8.low()

#---------------------------巡线部分---------------------------------

#uart = UART(3,115200,bits=8, parity=None, stop=1, timeout_char = 1000)   #uart初始化

#LED(1).on()
#LED(2).on()
#LED(3).on()

roi1 =     [(0,   55, 14, 20),         #1
            (28,  55, 14, 20),         #2
            (56,  55, 10, 20),         #3
            (88,  55, 10, 20),         #4
            (112, 55, 14, 20),         #5
            (140, 55, 14, 20)]         #6

roi2 =     [(14,55,14,20),         #5
            (42,55,14,20),         #7
            (66,55,22,20),
            (98,55,14,20),
            (126,55,14,20)
             ]
#160 120
sensor.reset() # 初始化摄像头
sensor.set_pixformat(sensor.RGB565) # 格式为 RGB565.
sensor.set_framesize(sensor.QQVGA)#160x120
sensor.skip_frames(time=20) # 跳过10帧，使新设置生效

sensor.set_auto_whitebal(True) # turn this off.
sensor.set_auto_gain(True) # must be turned off for color tracking

sensor.set_vflip(True)# 垂直方向翻转
sensor.set_hmirror(True)# 水平方向翻转

clock = time.clock()

#除红线外全是黑色，红线为白
#黑线阈值
GROUND_THRESHOLD=(0, 42, -78, 10, 73, -75)   #设定颜色区间

#红线阈值
GROUND_THRESHOLD1=(71, 12, 19, 127, 109, -4)

while(True):

    data=0

    blob1=None
    blob2=None
    blob3=None
    blob4=None
    blob5=None
    blob6=None

    blob7=None
    blob8=None
    blob9=None
    blob10=None
    blob11=None

    flag = [0,0,0,0,0,0,0,0,0,0,0]

    img = sensor.snapshot().lens_corr(strength = 1.7 , zoom = 1.0)#畸变矫正

    blob1 = img.find_blobs([GROUND_THRESHOLD1], roi=roi1[0]) #1号框
    blob2 = img.find_blobs([GROUND_THRESHOLD1], roi=roi1[1]) #2号框
    blob3 = img.find_blobs([GROUND_THRESHOLD1], roi=roi1[2]) #3号框
    blob4 = img.find_blobs([GROUND_THRESHOLD1], roi=roi1[3]) #4号框
    blob5 = img.find_blobs([GROUND_THRESHOLD1], roi=roi1[4]) #5号框
    blob6 = img.find_blobs([GROUND_THRESHOLD1], roi=roi1[5]) #6号框

    blob7 = img.find_blobs([GROUND_THRESHOLD], roi=roi2[0]) #黑1号框
    blob8 = img.find_blobs([GROUND_THRESHOLD], roi=roi2[1]) #黑2号框
    blob9 = img.find_blobs([GROUND_THRESHOLD], roi=roi2[2]) #黑3号框
    blob10 = img.find_blobs([GROUND_THRESHOLD], roi=roi2[3]) #黑4号框
    blob11 = img.find_blobs([GROUND_THRESHOLD], roi=roi2[4]) #黑5号框


    if blob1:
        flag[0] = 1  #1检测到红线
    if blob2:
        flag[1] = 1  #2检测到红线
    if blob3:
        flag[2] = 1  #3检测到红线
    if blob4:
        flag[3] = 1  #4检测到红线
    if blob5:
        flag[4] = 1  #5检测到红线
    if blob6:
        flag[5] = 1  #6检测到红线

    if blob7:
        flag[6] = 1  #黑1检测到黑线
    if blob8:
        flag[7] = 1  #黑2检测到黑线
    if blob9:
        flag[8] = 1  #黑3检测到黑线
    if blob10:
        flag[9] = 1  #黑2检测到黑线
    if blob11:
        flag[10] = 1  #黑3检测到黑线

    print(flag[0],flag[1],flag[2],flag[3],flag[4],flag[5],888,flag[6],flag[7],flag[8],flag[9],flag[10])

    if(flag[6] == 1 & flag[7] == 1 & flag[8] == 1 & flag[9] == 1 & flag[10] == 1
       | flag[6] == 1 & flag[7] == 1 & flag[9] == 1 & flag[10] == 1
       | flag[6] == 1 & flag[7] == 1
       | flag[9] == 1 & flag[10] == 1):

       p8.high()
       time.sleep_ms(100)
       print("P8STOP")
       p8.low()

    if(flag[0] == 1 & flag[1] == 1 & flag[2] == 1 & flag[3] == 1 & flag[4] == 1 & flag[5] == 1
       | flag[0] == 1 & flag[1] == 1 & flag[2] == 1 & flag[3] == 1
       | flag[1] == 1 & flag[2] == 1| flag[3] == 1 & flag[4] == 1
       | flag[2] == 1 & flag[5] == 1):

       p7.high()
       time.sleep_ms(100)
       print("P7STOP")
       p7.low()

    for rec in roi1:
        img.draw_rectangle(rec, color=(255,0,0))#绘制出roi区域
    for rec in roi2:
        img.draw_rectangle(rec, color=(0,0,0))#绘制出roi区域
