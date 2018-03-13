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
 bool controller::setMaxSpeed(unsigned char maxSpeed)
{
  _maxSpeed = maxSpeed;
}
 bool controller::setMinSpeed(unsigned char minSpeed)
{
  _minSpeed = minSpeed;
}
bool controller::followRobot(int referenceDistance)
{
  return maintainDistance(referenceDistance);
}
bool controller::maintainDistance(int referenceDistance)
{
  bool Status = true;
  
  _mySensor -> update(); //New standard added. Other rudamentary sensor libs should conform to this standard
  //_relativeDistance = getAverageDistance();
  _relativeDistance = _mySensor -> getDistance();
  _relativeDistance = 100; //Just to force the robot to keep moving (TEST)
  _relativeDirection = _mySensor -> getDirection();

 // TEST CODE
  if(_relativeDirection<-1)
  {
    _relativeDirection = -70;
  }
  else if(_relativeDirection>1)
  {
    _relativeDirection = 70;
  }
  else
  {
    _relativeDirection = 0;
  }
  
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
  _propotionalControl = posSaturate(_propotionalControl,_maxSpeed);
  
  if(_propotionalControl<_minSpeed)
  {
    _propotionalControl = 0;
  }

  //Check if front robot is there or not

  if(!(_mySensor -> isVisible()))
  {
    _propotionalControl = 0;
    _findMarkerFirstLoop = true;
    Status = false;
  }
  
  Serial.print(String("The relative distance is: ") + _relativeDistance);
  Serial.println(String(" SPD:") + _propotionalControl);
  Serial.println(String(" DIR:") + _relativeDirection);
  _myMotion->setSpeed(_propotionalControl); //Have to scale
  _myMotion->setDirection(_relativeDirection); //Have to scale
  _myMotion->run();

  return Status;
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
bool controller::findMarker()
{
  bool Status = false;

  if(_findMarkerFirstLoop)
  {   _findMarkerFirstLoop = false;
      _findMarkerStartTime = millis();
  
     if(_mySensor -> getDirection() > 0)
    {
      _lastDirectionSign = 1;
    }
    else
    {
      _lastDirectionSign = 0;
    }
    
  }

    _mySensor -> update();

  //Do Stuff here
  _myMotion->setSpeed(100);
  if(_lastDirectionSign)
  { 
    _myMotion->setDirection(80);
    Serial.println("Right");
  }
  else
  {
    _myMotion->setDirection(-80);
    Serial.println("Left");
  }
  _myMotion->run();
  
  if(_mySensor -> isVisible())
  {
    Status = true;
  }

  return Status;
  
}

