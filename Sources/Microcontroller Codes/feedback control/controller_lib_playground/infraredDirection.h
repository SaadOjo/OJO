/*
 A custom library written for IR direction sensor
 Library wrıtten by Syed Saad Saif
 */
#ifndef INFRARED_DIRECTION_H
#define INFRARED_DIRECTION_H

#include <Arduino.h>

class infraredDirection
{
  public:
    infraredDirection(int leftPin, int rightPin);
    bool init();
    float getDirection();
    float getRightVoltage();
    float getLeftVoltage();
  private:
    float _direction;
    float _leftVoltage;
    float _rightVoltage;
    int _leftCount;
    int _rightCount;
    int _pinLeft;
    int _pinRight;
    float _referenceVoltage = 5;
};

#endif
