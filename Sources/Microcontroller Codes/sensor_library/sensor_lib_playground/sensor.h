/*
 A custom library written for IR distance sensor
 Library wrıtten by Syed Saad Saif
 */
#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include "infraredDistance.h"
#include "Ultrasonic.h"

class sensor
{
  public:
    sensor();
    bool init();
    float getDistance();
    
  private:
    float _distance;
    infraredDistance _mySensor;
    
};

#endif
