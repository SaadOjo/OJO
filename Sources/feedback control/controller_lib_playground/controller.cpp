/*
 Controller library for EE493 Convoy Design Project.
 Uses external PID controller libraries

 Written by Syed Saad Saif
 11/25/2017
 */
#include "Arduino.h"
#include "controller.h"

controller::controller(sensor &sensor, robotMotion &motion):_mySensor(&sensor), _myMotion(&motion)
{
  
}
void controller::followRobot(int referenceDistance)
{
  maintainDistance(referenceDistance);
}
void controller::maintainDistance(int referenceDistance)
{
  
  _relativeDistance = getAverageDistance();
  _relativeDirection = _mySensor -> getDirection();
  
  _propotionalControl = _K_p *  (_relativeDistance - referenceDistance);

  _propotionalControl += _controllerBias; //Add bias term for steady state
 /*
  //Condition Output
  if(_propotionalControl>255)
  {
    _propotionalControl = 255;
  }
  if(_propotionalControl<0)
  {
    _propotionalControl = 0;
  }
  */

  _propotionalControl = posSaturate(_propotionalControl,255);
  _propotionalControl = map(_propotionalControl,0,255,0,100);

  Serial.print(String("The relative distance is: ") + _relativeDistance);
  Serial.println(String(" SPD:") + _propotionalControl);
  Serial.println(String(" DIR:") + _relativeDirection);
  _myMotion->setSpeed(_propotionalControl); //Have to scale
  _myMotion->setDirection(_relativeDirection); //Have to scale
  _myMotion->run();
}
int controller::getAverageDistance()
{
  int averageDistance = 0;
  
  _relativeDistanceArray[_ringCounter%AVERAGE_SAMPLES] = _mySensor -> getDistance(); //Overflow possible
  
  for (int i = 0 ; i<AVERAGE_SAMPLES;i++ )
  {
    averageDistance += _relativeDistanceArray[i];
  }
  _ringCounter++;
  return averageDistance/AVERAGE_SAMPLES;
  
}

