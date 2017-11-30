/*
 Controller library for EE493 Convoy Design Project.
 Uses external PID controller libraries

 Written by Syed Saad Saif
 11/25/2017
 */

#ifndef controller_h
#define controller_h

#include "infraredDistance.h"
#include "robotMotion.h"

class controller
{
  
  public:
  controller(infraredDistance &sensor, robotMotion &motion); //Sensor library will contain two sensors. It will take the best available data and send it to the controller
  void followRobot(int referenceDistance); //This code will run in the main loop

  private:
  
  void maintainDistance(int referenceDistance);  
  int _relativeDistance;
  int _propotionalControl;
  float _K_p = 20;
  int _controllerBias;
  
  infraredDistance *_mySensor;
  robotMotion *_myMotion;
  
 
};

#endif
