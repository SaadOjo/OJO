/*
 A custom library written for wireless lvdt LCD display
 Library wrıtten by Syed Saad Saif
 */
#include "sensor.h" 

sensor::sensor():_mySensor(1)
{
 
}

bool sensor::init(){
//Analog declaration
}

float sensor::getDistance()
{
  return _mySensor.getDistance();
}
