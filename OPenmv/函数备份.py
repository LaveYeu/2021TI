#函数备份



#--------------------------------------------------------------------------------------#
#传感器函数

sensor.set_vflip(False)# 垂直方向翻转

sensor.set_hmirror(False)# 水平方向翻转


#时钟函数
clock = time.clock()






#串口函数
uart = UART(1,9600,bits=8, parity=None, stop=1, timeout_char = 1000)
#LED函数
led = pyb.LED(3)
