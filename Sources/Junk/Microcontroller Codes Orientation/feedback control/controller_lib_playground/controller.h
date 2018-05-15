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
#define FIND_ROBOT_SWITCH_TIME 3 //seconds 

// Leaving

#define LATERAL_EXIT_TIME  1000 //(ms)
#define LATERAL_LEAVE_TURN_TIME  500 //(ms)

#define REJOIN_WAIT_TIME  1000
#define REJOIN_ENTRY_TIME  1000 //(ms)
#define REJOIN_LEAVE_TURN_TIME  500 //(ms)

#define MAINTAIN_VELOCITY_TIME 3000 //(ms)

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
  void avoidCollision(unsigned char avoidInfo);  
  bool findMarker();
  bool lateralExit();
  bool moveBack();
  bool rejoin();
  bool forceFirstLoop();
  bool forceMotors(unsigned char speed, unsigned char direction);
   

  private:

  //Common maneuver variables
  bool _maneuverFirstLoop = true; //on exit from a manever set this flag so that the other functions can reset their timers
  unsigned long int _maneuverStartTime;
  unsigned long int _maneuverTime;

  //Find Marker Function Status bits
  bool _lastDirectionSign = false; 
  bool _first = true;
  bool _turnModifier = false;


  //lateralExit Variables
  bool _leaveDirection = false;
  unsigned char _lastSpeed = 50;

  //maintain velocity 
  bool maintainVelocityBool = false;
  bool leavingRobotObservedFirstTime = true;
  unsigned long int maintainVelocityStartTime;
  
  
  bool maintainDistance(int referenceDistance);
  int getAverageDistance(); 
  void _maintainVelocity();
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
