/*
 A custom library written for OJO controller
 Library wrıtten by Syed Saad Saif
 */
#include "sensor.h" 

sensor::sensor():_mySensor(1),_myDirectionSensor(2,3)
{
 
}

bool sensor::init(){
//Analog declaration
}

float sensor::getDistance()
{
  return _mySensor.getDistance();
}
float sensor::getDirection()
{
  return _myDirectionSensor.getDirection();
}
