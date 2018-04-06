/*
 A custom library written for wireless lvdt LCD display
 Library wrıtten by Syed Saad Saif
 */
#include "collisionDetector.h"

collisionDetector::collisionDetector(unsigned char frontPin, unsigned char leftEchoPin, 
    unsigned char leftTriggerPin, unsigned char rightEchoPin, unsigned char rightTriggerPin,
    unsigned char backEchoPin, unsigned char backTriggerPin): _left(_leftTriggerPin, _leftEchoPin),
                                                              _right(_rightTriggerPin, _rightEchoPin),
                                                              _back(_backTriggerPin, _backEchoPin)

{
  _frontPin = frontPin;
  _leftEchoPin = leftEchoPin;
  _leftTriggerPin = leftTriggerPin;
  _rightEchoPin = rightEchoPin;
  _rightTriggerPin = rightTriggerPin;
  _backEchoPin = backEchoPin;
  _backTriggerPin = backTriggerPin; 
}

bool collisionDetector::init(){
    
  
//Analog declaration
}

float collisionDetector::getDanger()
{
  unsigned char danger=0;
  unsigned char leftDis, rightDis, backDis, minimum=DANGER_DISTANCE;
  leftDis = _left.distanceRead();
  rightDis = _right.distanceRead();
  backDis = _back.distanceRead();

  if(leftDis<minimum){
    minimum=leftDis;
    danger=1;}
  if(rightDis<minimum){
    minimum=rightDis;
    danger=2;}
  if(backDis<minimum){
    minimum=backDis;
    danger=3;}
    
  return danger;
}
