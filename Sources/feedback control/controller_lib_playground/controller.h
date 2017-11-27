/*
 Controller library for EE493 Convoy Design Project.
 Uses external PID controller libraries

 Written by Syed Saad Saif
 11/25/2017
 */

#ifndef controller_h
#define controller_h

class controller
{
  
  public:
  controller(motor &myMotor, sensor &mySensor); //Sensor library will contain two sensors. It will take the best available data and send it to the controller
  void followRobot(); //This code will run in the main loop

  private:
  int _operationMode;
  motor  *_myMotor;
  sensor *_mySensor;
  
  
};

#endif
