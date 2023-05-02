#Скрипт не доделан. Поэтому мусор в обработке.
import cv2 as cv
import numpy as np
import math
cap = cv.VideoCapture('20191119_1241_Cam_1_03_00.mp4')
while cap.isOpened():
    ret, frame = cap.read()
    # if frame is read correctly ret is True
    if not ret:
        print("Can't receive frame (stream end?). Exiting ...")
        break
    gray=cv.cvtColor(frame,cv.COLOR_BGR2GRAY)
    

    dst = cv.Canny(gray,50,150)
    #lines = cv.HoughLines(edges, 1, np.pi / 180, 15, 10, 3)
    lines = cv.HoughLines(dst, 1, math.pi / 180, 15, np.array([]), 10, 3)
    a,b,c = lines.shape
    for i in range(a):
        rho = lines[i][0][0]
        theta = lines[i][0][1]
        a = math.cos(theta)
        b = math.sin(theta)
        x0, y0 = a*rho, b*rho
        pt1 = ( int(x0+1000*(-b)), int(y0+1000*(a)) )
        pt2 = ( int(x0-1000*(-b)), int(y0-1000*(a)) )
        cv.line(dst, pt1, pt2, (255, 255, 255), 2, cv.LINE_AA)

    cv.imshow('frame', dst)
    #cv.waitKey(0)
    if cv.waitKey(1) == ord('q'):
        break
cap.release()
cv.destroyAllWindows()