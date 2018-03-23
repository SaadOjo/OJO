/*
 A custom library written for IR distance sensor
 Library wrıtten by Syed Saad Saif
 */
#ifndef FLAGS_H
#define FLAGS_H

#include <Arduino.h>

class flags
{
  public:
    flags(unsigned char solarPin_1, unsigned char solarPin_2);
    bool init();
    float getSolarLastOneFlag();
  private:
    float _distance;
    float _voltage;
    int _count;
    int _pin;
    float _referenceVoltage = 5;
};

#endif
