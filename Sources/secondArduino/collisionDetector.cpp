/*
 A custom library written for wireless lvdt LCD display
 Library wrıtten by Syed Saad Saif
 */
#include "collisionDetector.h"

collisionDetector::collisionDetector(unsigned char frontPin, unsigned char leftEchoPin, 
    unsigned char leftTriggerPin, unsigned char rightEchoPin, unsigned char rightTriggerPin,
    unsigned char backEchoPin, unsigned char backTriggerPin): _left(leftTriggerPin, leftEchoPin),
                                                              _right(rightTriggerPin, rightEchoPin),
                                                              _back(backTriggerPin, backEchoPin)

{
  
}

bool collisionDetector::init(){
    
  
//Analog declaration
}

unsigned char collisionDetector::getAvoidAction()
{
  unsigned char danger=0;
  unsigned char leftDis, rightDis, backDis, minimum=DANGER_DISTANCE;
  leftDis = _left.distanceRead();
  if(!leftDis)
  {
    leftDis = 255;
  }
  rightDis = _right.distanceRead();
  if(!rightDis)
  {
    rightDis = 255;
  }
  backDis = _back.distanceRead();
  if(!backDis)
  {
    backDis = 255;
  }


  if(leftDis<minimum){
    minimum=leftDis;
    danger=1;}
  if(rightDis<minimum){
    minimum=rightDis;
    danger=2;}
  if(backDis<minimum){
    minimum=backDis;
    danger=3;}

    //Serial.println(String("Left: ") + leftDis + ",Right: " + rightDis +  " ,Back: " + backDis);
    
  return danger;
}
