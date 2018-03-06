/*
 A custom library written for IR direction sensor
 Library wrıtten by Syed Saad Saif
 */
#ifndef INFRARED_DIRECTION_H
#define INFRARED_DIRECTION_H

#include <Arduino.h>

#define VISIBLE_THRESHOLD 0.3

class infraredDirection
{
  public:
    infraredDirection(int leftPin, int rightPin);
    bool init();
    bool update();
    bool isVisible();
    int getDistance();
    float getDirection();
    float getRightVoltage();
    float getLeftVoltage();
  private:
    float _direction;
    float _leftVoltage;
    float _rightVoltage;
    float _maxVoltage;
    int _leftCount;
    int _rightCount;
    int _pinLeft;
    int _pinRight;
    float _referenceVoltage = 5;
};

#endif
