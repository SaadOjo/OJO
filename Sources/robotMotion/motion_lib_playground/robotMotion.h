/*
 A custom library written for IR distance sensor
 Library wrıtten by Syed Saad Saif
 */
#ifndef ROBOT_MOTION_H
#define ROBOT_MOTION_H

#include <Arduino.h>

class robotMotion
{
  public:
    robotMotion(int pin);
    bool setSpeed();
    bool setDirection();
    bool setRightSpeed();
    bool setLeftSpeed();
    bool init();

  private:
  int _pin;
};

#endif
