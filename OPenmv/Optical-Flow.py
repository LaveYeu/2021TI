# 光流差动平移变换示例

#
# 此示例显示使用OpenMV Cam通过将当前图像与先前图像相互比较来测量X和Y方向的平移。
# 请注意，在此模式下只处理X和Y平移 - 而不是旋转/缩放。

# 要有效地运行此演示，请将OpenMV Cam安装在稳定的底座上，
# 然后慢慢将其转换为左，右，上和下，并观察数字的变化。
# 请注意，您可以看到位移数字+ - 水平和垂直分辨率的一半。


import sensor, image, time

# 注意！！！ 使用find_displacement()时，必须使用2的幂次方分辨率。
# 这是因为该算法由称为相位相关的东西提供动力，该相位相关使用FFT进行图像比较。
# 非2的幂次方分辨率要求填充到2的幂，这降低了算法结果的有用性。
# 请使用像B64X64或B64X32这样的分辨率（快2倍）。

# 您的OpenMV Cam支持2的幂次方分辨率64x32,64x64,128x64和128x128。
# 如果您想要32x32的分辨率，可以通过在64x64图像上执行“img.pool（2,2）”来创建它。

sensor.reset()                      # 复位并初始化传感器。
#sensor.set_pixformat(sensor.RGB565) # Set pixel format to RGB565 (or GRAYSCALE)
#设置图像色彩格式，有RGB565色彩图和GRAYSCALE灰度图两种
sensor.set_pixformat(sensor.GRAYSCALE)

sensor.set_framesize(sensor.B64X32)   # 将图像大小设置为64x64…… (64x32)……


sensor.skip_frames(time = 10)     # 等待设置生效。
clock = time.clock()                # 创建一个时钟对象来跟踪FPS帧率。

# 从主帧缓冲区的RAM中取出以分配第二帧缓冲区。
# 帧缓冲区中的RAM比MicroPython堆中的RAM多得多。
# 但是，在执行此操作后，您的某些算法的RAM会少得多......
# 所以，请注意现在摆脱RAM问题要容易得多。
extra_fb = sensor.alloc_extra_fb(sensor.width(), sensor.height(), sensor.GRAYSCALE)
extra_fb.replace(sensor.snapshot())

while(True):
    clock.tick() # 追踪两个snapshots()之间经过的毫秒数。
    img = sensor.snapshot() # 拍一张照片并返回图像。

    img.draw_cross(32, 18, color = (255, 255, 255), size = 5, thickness = 1)

    displacement = extra_fb.find_displacement(img)
    extra_fb.replace(img)

    # 没有滤波，偏移结果是嘈杂的，所以我们降低了一些精度。
    sub_pixel_x = int(displacement.x_translation() * 30)/5
    sub_pixel_y = int(displacement.y_translation() * 30)/5

    if(displacement.response() > 0.3): # 低于0.1左右（YMMV），结果只是噪音。
 #        print("x:{0} y:{1}".format(sub_pixel_x, sub_pixel_y,
 #              displacement.response(),
 #              clock.fps()))
          print("x:{0} y:{1}".format(sub_pixel_x, sub_pixel_y,
                displacement.response(),
                clock.fps()))
    else:
        print("{}")
