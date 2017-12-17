/*
 A custom library written for IR distance sensor
 Library wrıtten by Syed Saad Saif
 */
#ifndef ROBOT_MOTION_H
#define ROBOT_MOTION_H

#include <Arduino.h>
#include "signalConditioner.h"

class robotMotion
{
  public:
    robotMotion(int motor_1_in_1, int motor_1_in_2, int motor_2_in_1, int motor_2_in_2);
    bool run();
    bool setSpeed(unsigned short int speed);
    bool setDirection(short int direction);
    bool runRight(unsigned short int speed); 
    bool runLeft(unsigned short int speed); 
    bool init();

  private:
    int _motor_1_in_1;
    int _motor_1_in_2; 
    int _motor_2_in_1; 
    int _motor_2_in_2;
    int _leftCalibrationFactor = 100; //Percentage
    int _rightCalibrationFactor = 100; //Percentage
    int _speed;
    int _direction;
};

#endif
