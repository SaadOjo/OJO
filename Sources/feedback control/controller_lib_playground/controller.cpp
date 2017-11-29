/*
 Controller library for EE493 Convoy Design Project.
 Uses external PID controller libraries

 Written by Syed Saad Saif
 11/25/2017
 */
 
#include "Arduino.h"
#include "controller.h"


controller::controller(infraredDistance &sensor):_mySensor(&sensor)
{
  
}
void controller::followRobot(int referenceDistance)
{
  maintainDistance(referenceDistance);
}
void controller::maintainDistance(int referenceDistance)
{
  _relativeDistance = _mySensor -> getDistance();
  _propotionalControl = _K_p * (referenceDistance - _relativeDistance);
  Serial.println(String("The relative distance is: ") + _relativeDistance);
  Serial.println(String("The controller output is: ") + _propotionalControl);
  //myMotion.setSpeed(_propotionalControl); //Have to scale
}

