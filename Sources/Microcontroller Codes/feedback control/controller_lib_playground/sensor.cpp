/*
 A custom library written for OJO controller
 Library wrıtten by Syed Saad Saif
 */
#include "sensor.h" 

sensor::sensor():_mySensor(1),_myDirectionSensor(2,3),_mySolarFlag(2,3)
{
 
}

bool sensor::init(){
//Analog declaration
}
bool sensor::update()
{
  _myDirectionSensor.update();
  _mySolarFlag.update();
  //Update the distance sensor as well
}
unsigned char sensor::isVisible()
{
  unsigned char visibility = 0;
  //Visibility Standard
  //0 : No sensor visible
  //1 : All sensors visible
  //2 : Primary sensor visible only
  //3 : Secondary sensor visible only
  if(_myDirectionSensor.isVisible())
  {
    visibility = 1;
  }
  return visibility;
  //Update the distance sensor as well
}


float sensor::getDistance()
{
  float distance = _mySensor.getDistance();
    distance = _myDirectionSensor.getDistance();
  return distance;
  //Take direction from the other sensor as well
}
float sensor::getDirection()
{
  return _myDirectionSensor.getDirection();
}
unsigned char sensor::getLastOneFlagStatus()
{
  return _mySolarFlag.getSolarLastOneFlag();
}
