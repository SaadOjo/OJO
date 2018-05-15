/*
 A custom library written for IR direction sensor
 Library wrıtten by Syed Saad Saif
 */
#ifndef INFRARED_DIRECTION_H
#define INFRARED_DIRECTION_H

#include <Arduino.h>

#define VISIBLE_THRESHOLD 0.3
#define DATA_CONSIDERED 3

class infraredDirection
{
  public:
    infraredDirection(int leftPin, int rightPin);
    bool init();
    bool update();
    bool isVisible();
    float getDistance();
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
    void _addData(int data);
    bool _detectSignChange();
    unsigned char noOfData;
    unsigned char _circularIncrement(unsigned char num);
    float _referenceVoltage = 5;
    int _array[DATA_CONSIDERED] = {1, -1 ,3};
    int _pointer;
};

#endif
