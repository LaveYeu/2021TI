THRESHOLD = (59, 25, 127, 19, -128, 89) # Grayscale threshold for dark things...
import sensor, image, time
from pyb import LED
import car
from pid import PID
rho_pid = PID(p=0.4, i=0)
theta_pid = PID(p=0.001, i=0)

#LED(1).on()
#LED(2).on()
#LED(3).on()

sensor.reset()
sensor.set_vflip(False)
sensor.set_hmirror(False)
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQQVGA) # 80x60 (4,800 pixels)
sensor.skip_frames(time = 20)     # WARNING: If you use QQVGA it may take seconds
clock = time.clock()                # to process a frame sometimes.

min_degree = 80
max_degree = 120

while(True):
    clock.tick()
    img = sensor.snapshot().binary([THRESHOLD])
    line = img.get_regression([(100,100)], robust = True)
    for l in img.find_lines(threshold = 4000, theta_margin = 25, rho_margin = 25):
            if (min_degree <= l.theta()) and (l.theta() <= max_degree):
                img.draw_line(l.line(), color = (255, 0, 0))
    if (line):
        rho_err = abs(line.rho())-img.width()/2
        if line.theta()>90:
            theta_err = line.theta()-180
        else:
            theta_err = line.theta()
        img.draw_line(line.line(), color = 127)
        print(rho_err,line.magnitude(),rho_err)
        if line.magnitude()>8:
            #if -40<b_err<40 and -30<t_err<30:
            rho_output = rho_pid.get_pid(rho_err,1)
            theta_output = theta_pid.get_pid(theta_err,1)
            output = rho_output+theta_output
            car.run(50+output, 50-output)
        else:
            car.run(0,0)
    else:
        car.run(50,-50)
        pass
    #print(clock.fps())
