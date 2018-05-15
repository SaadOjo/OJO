/*
 A custom library written for wireless lvdt LCD display
 Library wrıtten by Syed Saad Saif
 */
#include "collisionDetector.h"

collisionDetector::collisionDetector(unsigned char frontPin, unsigned char leftEchoPin, 
    unsigned char leftTriggerPin, unsigned char rightEchoPin, unsigned char rightTriggerPin,
    unsigned char backEchoPin, unsigned char backTriggerPin): _left(leftTriggerPin, leftEchoPin),
                                                              _right(rightTriggerPin, rightEchoPin),
                                                              _back(backTriggerPin, backEchoPin),_front(frontPin)

{
  
}

bool collisionDetector::init(){

}

bool collisionDetector::update()
{
  _leftDist = _left.distanceRead();
  _rightDist = _right.distanceRead();
  _backDist = _back.distanceRead();
  _frontDist = _front.getDistance();

  if(!_leftDist)
  {
    _leftDist = 255;
  }
  
  if(!_rightDist)
  {
    _rightDist = 255;
  }
  
  if(!_backDist)
  {
    _backDist = 255;
  }

  if(!_frontDist)
  {
    _frontDist = 255;
  }

}

unsigned char collisionDetector::getAvoidAction()
{
  unsigned char avoidAction=0;
  unsigned char minimum=DANGER_DISTANCE;
  
  if(_leftDist<minimum)
  {
    minimum=_leftDist;
    avoidAction = 1;
  }
  if(_rightDist<minimum)
  {
    minimum=_rightDist;
    avoidAction = 2;
  }
  if(_backDist<minimum)
  {
    minimum=_backDist;
    avoidAction = 3;
  }
  if(_frontDist<minimum)
  {
    minimum=_frontDist;
    avoidAction = 4;
  }

    Serial.println(String("Left: ") + _leftDist + ",Right: " + _rightDist +  " ,Back: " + _backDist + ",Front: " + _frontDist);
    
  return avoidAction;
}

bool collisionDetector::robotIsLast()
{
  bool robotInFront, robotInBack;

  bool robotIsLast;
  
  if(_frontDist < LAST_DETERMINE_DISTANCE)
  {
    robotInFront = true;
  }
  else
  {
    robotInFront = false;
  }
  
  if(_backDist < LAST_DETERMINE_DISTANCE)
  {
    robotInBack = true;
  }
  else
  {
    robotInBack = false;
  }

  if(robotInFront &&!robotInBack)
  {
      robotIsLast = true;
  }
  else
  {
      robotIsLast = false;
  }

  return robotIsLast;
  
}
