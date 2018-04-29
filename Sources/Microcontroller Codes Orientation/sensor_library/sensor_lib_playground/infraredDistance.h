/*
 A custom library written for IR distance sensor
 Library wrıtten by Syed Saad Saif
 */
#ifndef INFRARED_DISTANCE_H
#define INFRARED_DISTANCE_H

#include <Arduino.h>

class infraredDistance
{
  public:
    infraredDistance(int pin);
    bool init();
    float getDistance();
  private:
    float _distance;
    float _voltage;
    int _count;
    int _pin;
    float _referenceVoltage = 5;
};

#endif
