import cv2
import numpy as np
import math

cap = cv2.VideoCapture(0)
    #calculate angle
def angle(pt1,pt2,pt0):
    dx1 = pt1[0][0] - pt0[0][0]
    dy1 = pt1[0][1] - pt0[0][1]
    dx2 = pt2[0][0] - pt0[0][0]
    dy2 = pt2[0][1] - pt0[0][1]
    return float((dx1*dx2 + dy1*dy2))/math.sqrt(float((dx1*dx1 + dy1*dy1))*(dx2*dx2 + dy2*dy2) + 1e-10)
while(1):

    # Take each frame
    ret, frame = cap.read()
    # Convert BGR to HSV
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # define range of green color in HSV
    sensitivity = 25;
    lower_green = np.array([60-sensitivity,100,50])
    upper_green = np.array([60+sensitivity,255,255])

    # Threshold the HSV image to get only green colors
    mask = cv2.inRange(hsv, lower_green, upper_green)

    # Bitwise-AND mask and original image
    res = cv2.bitwise_and(frame,frame, mask= mask)
    #edge detection
##    edges = cv2.Canny(res,100,200)





    #Capture frame-by-frame
    
    if ret==True:
        #grayscale
        gray = cv2.cvtColor(res, cv2.COLOR_BGR2GRAY)
        #Canny
        canny = cv2.Canny(res,100,200)

        #contours
        canny2, contours, hierarchy = cv2.findContours(canny,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)
        for i in range(0,len(contours)):
            #approximate the contour with accuracy proportional to
            #the contour perimeter
            approx = cv2.approxPolyDP(contours[i],cv2.arcLength(contours[i],True)*0.02,True)

            #Skip small or non-convex objects
            if(abs(cv2.contourArea(contours[i]))<100 or not(cv2.isContourConvex(approx))):
                continue

        
            if(len(approx)>=4 and len(approx)<=6):
                #nb vertices of a polygonal curve
                vtc = len(approx)
                #get cos of all corners
                cos = []
                for j in range(2,vtc+1):
                   cos.append(angle(approx[j%vtc],approx[j-2],approx[j-1]))
                #sort ascending cos
                cos.sort()
                #get lowest and highest
                mincos = cos[0]
                maxcos = cos[-1]

                #Use the degrees obtained above and the number of vertices
                #to determine the shape of the contour
                x,y,w,h = cv2.boundingRect(contours[i])
                if(vtc==4):
                      cv2.rectangle(res,(x,y),(x+w,y+h),(0,255,0),2)
##                    cv2.putText(frame,'RECT',(x,y),cv2.FONT_HERSHEY_SIMPLEX,scale,(255,255,255),2,cv2.LINE_AA)

    cv2.imshow('frame',frame)
    cv2.imshow('mask',mask)
    cv2.imshow('res',res)
##    cv2.imshow('edge detection',edges)
   
    

    if cv2.waitKey(5) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()
