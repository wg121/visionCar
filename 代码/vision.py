# Untitled - By: 28858 - 周三 4月 6 2022

def detect(coordinate,threshold1,threshold2):#查找色块中心坐标与上下限的关系
    if(coordinate>threshold1 and coordinate<threshold2):#在上下限之间
        return 1
    elif(coordinate<=threshold1):#偏向小一侧
        return 2
    elif(coordinate>=threshold2):#偏向大一侧
        return 3
    else:
        return 0#各种奇怪的错误


class command(object):#定义command类（类似结构体），具有com属性储存位置值，MoveCommand方法（类似函数）进行处理
    def __init__(self,com):
        self.com = com
    def MoveCommand(self,name,direction,word):
        OffsetDictMin = {'direct':'L','l/r':'up'}#left
        OffsetDictMax = {'direct':'R','l/r':'down'}#'right'
        OffsetMin = OffsetDictMin[direction]
        OffsetMax = OffsetDictMax[direction]

        if (name == 1):
            self.com = word
        elif(name == 2):
            self.com = OffsetMin
        elif(name == 3):
            self.com = OffsetMax
        elif(name == 0):
            pass


#THRESH2 = (22,32)#灰度图下巡线
THRESH2 =(14, 58)#阈值，识别该值内的色块
#THRESH2 =(8, 45)
import sensor, image, time,pyb
from pyb import UART
roiDOWN = (40,80,95,40)#五个roi，用于框定识别区域
roiMAIN = (40,40,95,40)
roiUP = (40,0,95,40)
roiLEFT = (0,40,15,40)
roiRIGHT = (145,40,15,40)
flag_last = 0
uart_receive = 0
flag1 = 0
flagnull = 0
flagturn = 0
uart = UART(3,115200,bits=8, parity=None, stop=1, timeout_char = 1000)

sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QQVGA)#过大容易超ram,QQVGA:160x120
#中心55，95，左中心5，35；45，75  右中心125，155；45，75
sensor.skip_frames(time = 2000)

clock = time.clock()
sign = 1
while(True):
    clock.tick()
    img = sensor.snapshot()
    img.lens_corr(strength = 1.8)
   # img.binary([THRESHOLD])
    img.median(1, percentile=0.5)#中值滤波，percentile过大会增大误差（断线）
    img.mean(2)
    img.draw_rectangle(roiUP,color = 0)#在图像中画出区域
    img.draw_rectangle(roiMAIN,color = 0)
    img.draw_rectangle(roiDOWN,color = 0)
    img.draw_rectangle(roiLEFT,color = 0)
    img.draw_rectangle(roiRIGHT,color = 0)

    flagD = 0
    flagM = 0
    flagU = 0
    flagL = 0
    flagR = 0
#找出各个roi中的色块

    for blobD in img.find_blobs([THRESH2],roi = roiDOWN,merge = True,margin = 25):
#开始寻找色块，找到后框定范围，标出中心
        img.draw_rectangle(blobD.rect(),color = 255)
        img.draw_cross(blobD.cx(),blobD.cy(),color = 255)
        if(blobD):
            flagD = detect(blobD.cx(),75,85)

    for blobM in img.find_blobs([THRESH2],roi = roiMAIN,merge = True,margin = 25):
        img.draw_rectangle(blobM.rect(),color = 255)
        img.draw_cross(blobM.cx(),blobM.cy(),color = 255)
        if(blobM):
            flagM = detect(blobM.cx(),65,95)

    for blobU in img.find_blobs([THRESH2],roi = roiUP,merge = True,margin = 25):
        img.draw_rectangle(blobU.rect(),color = 255)
        img.draw_cross(blobU.cx(),blobU.cy(),color = 255)
        if(blobU):
            flagU = detect(blobU.cy(),0,20)

    for blobL in img.find_blobs([THRESH2],roi = roiLEFT,merge = True,margin = 25):
        img.draw_rectangle(blobL.rect(),color = 255)
        img.draw_cross(blobL.cx(),blobL.cy(),color = 255)
        if(blobL):
            flagL = detect(blobL.cy(),50,50)

    for blobR in img.find_blobs([THRESH2],roi = roiRIGHT,merge = True,margin = 25):
        img.draw_rectangle(blobR.rect(),color = 255)
        img.draw_cross(blobR.cx(),blobR.cy(),color = 255)
        if(blobR):
            flagR = detect(blobR.cy(),50,50)
    comm1 = command('N')# 初始化为未检测
    comm2 = command('N')
    commL = command('N')
    commR = command('N')
    commD = command('N')
    comm1.MoveCommand(flagD,'direct','S')#notend是无意义辅助词，表示判断未结束
    flagDWeight = 3
    flagMWeight = 2
    flagOffset = ((flagDWeight * flagD)+(flagMWeight * flagM))/(flagDWeight + flagMWeight)#加权处理，未使用



    commR.MoveCommand(flagR,'l/r','Notend')
    commL.MoveCommand(flagL,'l/r','Notend')
    commD.MoveCommand(flagD,'direct','S')
    if(uart.any()):#uart收到
        uart_receive = uart.readchar()
        #comm1.com = 'N'
        print(uart_receive)


    if(((not commR.com == 'N') or (not commL.com == 'N'))):#检测到C
        comm1.com = 'C'
        #print(comm1.com)
        if(not comm1.com == flag_last):#如果与上一个检测值不同则发送
            #uart_receive = 0
            print(comm1.com)
            uart.write(comm1.com)
            flag_last = comm1.com


    if(uart_receive == 54):#'T'
        flagturn = 1
    if(uart_receive == 78):#'N'
        flagnull = 1


    while(flagturn == 1):#由于图像截取和处理每一帧都必须进行，需要在while里添加
         img = sensor.snapshot()
        img.lens_corr(strength = 1.8)
       # img.binary([THRESHOLD])
        img.median(1, percentile=0.5)#中值滤波，percentile过大会增大误差（断线）
        img.mean(2)
        for blobD in img.find_blobs([THRESH2],roi = roiDOWN,merge = True,margin = 25):
            img.draw_rectangle(blobD.rect(),color = 255)
            img.draw_cross(blobD.cx(),blobD.cy(),color = 255)
            if(blobD):
                flagD = detect(blobD.cx(),75,85)
        for blobM in img.find_blobs([THRESH2],roi = roiMAIN,merge = True,margin = 25):
            img.draw_rectangle(blobM.rect(),color = 255)
            img.draw_cross(blobM.cx(),blobM.cy(),color = 255)
            if(blobM):
                flagM = detect(blobM.cx(),65,95)

        for blobU in img.find_blobs([THRESH2],roi = roiUP,merge = True,margin = 25):
            img.draw_rectangle(blobU.rect(),color = 255)
            img.draw_cross(blobU.cx(),blobU.cy(),color = 255)
            if(blobU):
                flagU = detect(blobU.cy(),0,20)

        for blobL in img.find_blobs([THRESH2],roi = roiLEFT,merge = True,margin = 25):
            img.draw_rectangle(blobL.rect(),color = 255)
            img.draw_cross(blobL.cx(),blobL.cy(),color = 255)
            if(blobL):
                flagL = detect(blobL.cy(),50,50)

        for blobR in img.find_blobs([THRESH2],roi = roiRIGHT,merge = True,margin = 25):
            img.draw_rectangle(blobR.rect(),color = 255)
            img.draw_cross(blobR.cx(),blobR.cy(),color = 255)
            if(blobR):
                flagR = detect(blobR.cy(),50,50)
        comm1 = command('N')# 初始化为未检测
        commL = command('N')
        commR = command('N')
        comm1.MoveCommand(flagD,'direct','S')#notend是无意义辅助词，表示判断未结束
        commR.MoveCommand(flagR,'l/r','Notend')
        commL.MoveCommand(flagL,'l/r','Notend')
        if( commR.com == 'N' and commL.com == 'N' and comm1 == 'N'):#检测到N
            uart.write(comm1.com)
            print(comm1.com)
            flagturn = 0
            flag_last = comm1.com
            uart_receive = 0

    while( flagnull ==  1):
        img = sensor.snapshot()
        img.lens_corr(strength = 1.8)
       # img.binary([THRESHOLD])
        img.median(1, percentile=0.5)#中值滤波，percentile过大会增大误差（断线）
        img.mean(2)
        for blobD in img.find_blobs([THRESH2],roi = roiDOWN,merge = True,margin = 25):
            img.draw_rectangle(blobD.rect(),color = 255)
            img.draw_cross(blobD.cx(),blobD.cy(),color = 255)
            if(blobD):
                flagD = detect(blobD.cx(),75,85)
        for blobM in img.find_blobs([THRESH2],roi = roiMAIN,merge = True,margin = 25):
            img.draw_rectangle(blobM.rect(),color = 255)
            img.draw_cross(blobM.cx(),blobM.cy(),color = 255)
            if(blobM):
                flagM = detect(blobM.cx(),65,95)

        for blobU in img.find_blobs([THRESH2],roi = roiUP,merge = True,margin = 25):
            img.draw_rectangle(blobU.rect(),color = 255)
            img.draw_cross(blobU.cx(),blobU.cy(),color = 255)
            if(blobU):
                flagU = detect(blobU.cy(),0,20)

        for blobL in img.find_blobs([THRESH2],roi = roiLEFT,merge = True,margin = 25):
            img.draw_rectangle(blobL.rect(),color = 255)
            img.draw_cross(blobL.cx(),blobL.cy(),color = 255)
            if(blobL):
                flagL = detect(blobL.cy(),50,50)

        for blobR in img.find_blobs([THRESH2],roi = roiRIGHT,merge = True,margin = 25):
            img.draw_rectangle(blobR.rect(),color = 255)
            img.draw_cross(blobR.cx(),blobR.cy(),color = 255)
            if(blobR):
                flagR = detect(blobR.cy(),50,50)
        comm1.MoveCommand(flagD,'direct','S')#notend是无意义辅助词，表示判断未结束
        if( (comm1.com == 'S') ):#检测到S
            uart.write(comm1.com)
            print(comm1.com)
            flagnull = 0
            flag_last = comm1.com
            uart_receive = 0



    if(not uart_receive == 78 and not uart_receive == 54):#正常处理，用于直线
        if(not comm1.com == flag_last):
            if(not comm1.com == 'C'):
                print(comm1.com)
                uart.write(comm1.com)
                flag_last = comm1.com

            #print(uart_receive)








