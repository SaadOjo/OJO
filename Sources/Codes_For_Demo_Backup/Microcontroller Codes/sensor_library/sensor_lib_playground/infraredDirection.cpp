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
bool infraredDirection::update(){
//Analog declaration
_leftVoltage =  getLeftVoltage();
_rightVoltage = getRightVoltage();
_maxVoltage = max(_leftVoltage, _rightVoltage);

}
bool infraredDirection::isVisible()
{
  bool visibility = false;
  Serial.println(String("max voltage:") + _maxVoltage);
  if(_maxVoltage > VISIBLE_THRESHOLD)
  {
    visibility = true;
  }
  return visibility;
}

float infraredDirection::getDistance()
{
  float distance = 0;
  float voltageAverage = (_rightVoltage + _leftVoltage)/2;
  distance = 34.48*1/sqrt(voltageAverage);
  return distance;
}

float infraredDirection::getDirection()
{
  _direction = (_rightVoltage - _leftVoltage)*20; //don't need saturation (no scaling required)

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
