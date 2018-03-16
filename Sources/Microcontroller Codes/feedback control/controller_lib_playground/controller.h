/*
 Controller library for EE493 Convoy Design Project.
 Uses external PID controller libraries

 Written by Syed Saad Saif
 11/25/2017
 */

#ifndef controller_h
#define controller_h

#define LEFT 0
#define RIGHT 1

//Maneuvers Parameters
#define FIND_ROBOT_SWITCH_TIME 5 //seconds 

#define AVERAGE_SAMPLES 10

#include "sensor.h"
#include "robotMotion.h"
#include "signalConditioner.h"

class controller
{
  
  public:
  controller(sensor &sensor, robotMotion &motion); //Sensor library will contain two sensors. It will take the best available data and send it to the controller
  bool followRobot(int referenceDistance); //This code will run in the main loop
  bool setMaxSpeed(unsigned char maxSpeed);
  bool setMinSpeed(unsigned char minSpeed);  
  bool findMarker();

  private:


  //Common maneuver variables
  bool _maneuverFirstLoop = true; //on exit from a manever set this flag so that the other functions can reset their timers
  unsigned int _maneuverStartTime;

  //Find Marker Function Status bits
  bool _lastDirectionSign = false; 
  bool _first = true;
  bool _turnModifier = false;
  
  
  
  bool maintainDistance(int referenceDistance);
  int getAverageDistance(); 
  int _relativeDistance;
  int _relativeDirection;
  int _propotionalControl;
  unsigned char _maxSpeed = 100;
  unsigned char _minSpeed = 0;
  float _K_p = 5;
  int _controllerBias;

  
  int _relativeDistanceArray[AVERAGE_SAMPLES];
  unsigned short int _ringCounter = 0;
  sensor *_mySensor;
  robotMotion *_myMotion;
  
 
};

#endif
