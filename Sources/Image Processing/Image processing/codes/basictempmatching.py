import cv2
import numpy as np

#load the image and convert to gray scale
image = cv2.imread('4temp.jpg')
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
#load the template and note the dimensions
template = cv2.imread('temp.jpg',0)
w, h = template.shape[::-1]
#check macthing between image and template with threshold of 80%
#and find locations where res is greater than or equal to 80%.
res = cv2.matchTemplate(gray,template,cv2.TM_CCOEFF_NORMED)
threshold = 0.8
loc = np.where( res >= threshold)
#mark the matches on the real image 
for pt in zip(*loc[::-1]):
    cv2.rectangle(image, pt, (pt[0] + w, pt[1] + h), (0,255,255), 2)

cv2.imshow('Detected',image)
cv2.waitKey(0)

