/*
 A custom library written for wireless lvdt LCD display
 Library wrıtten by Syed Saad Saif
 */
#include "infraredDistance.h"

infraredDistance::infraredDistance(int pin)
{
  _pin = pin;
 
}

bool infraredDistance::init(){
//Analog declaration
}

float infraredDistance::getDistance()
{
  _count = analogRead(_pin);
  _distance = (float)_count*_referenceVoltage/1024;
  return _distance;
}
