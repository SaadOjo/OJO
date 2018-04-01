/*
 A custom library written for IR distance sensor
 Library wrıtten by Syed Saad Saif
 */
#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include "infraredDistance.h"
#include "Ultrasonic.h"
#include "infraredDirection.h"
#include "flags.h"



class sensor
{
  public:
    sensor();
    bool init();
    bool update();
    unsigned char isVisible();
    unsigned char getLastOneFlagStatus();
    float getDistance();
    float getDirection();
    
  private:
    float _distance;
    infraredDistance _mySensor;
    infraredDirection _myDirectionSensor;
    flags _mySolarFlag;
    
    
};

#endif
