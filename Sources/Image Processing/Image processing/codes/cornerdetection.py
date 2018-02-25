import numpy as np
import cv2

#load the image and convert it to gray and then to float32
image=cv2.imread('example_image.jpg')
gray=cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
gray=np.float32(gray)

#detect corners with the goodFeaturesToTrack function
#parameters are as follows (image, max corners to detect, quality(between 0-1), and minimum euclidean distance between corners)
corners = cv2.goodFeaturesToTrack(gray, 25, 0.01, 20)
corners = np.int0(corners)

for corner in corners:
    x,y = corner.ravel()
    cv2.circle(image,(x,y),3,255,-1)
    
cv2.imshow('Corner',image)
cv2.waitKey(0)

