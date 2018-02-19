/*
 A custom library written IR direction sensor
 Library wrıtten by Syed Saad Saif
 */
#include "infraredDirection.h"

infraredDirection::infraredDirection(int pinLeft, int pinRight)
{
  _pinLeft = pinLeft;
  _pinRight = pinRight;
 
}

bool infraredDirection::init(){
//Analog declaration
}

float infraredDirection::getDirection()
{
  _direction = (getRightVoltage() - getLeftVoltage())*20; //don't need saturation (no scaling required)

  return _direction;
}

float infraredDirection::getLeftVoltage()
{
  _leftCount = analogRead(_pinLeft);
  _leftVoltage = (float)_leftCount*_referenceVoltage/1024;
  return _leftVoltage;
}

float infraredDirection::getRightVoltage() //don't store for values (for optimisation)
{
  _rightCount = analogRead(_pinRight);
  _rightVoltage = (float)_rightCount*_referenceVoltage/1024;
  return _rightVoltage;
}


//calibrate using average voltage of sensors
