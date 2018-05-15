/*
 A custom library written for IR distance sensor
 Library wrıtten by Syed Saad Saif
 */
#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include "infraredDirection.h"
#include "flags.h"
#include "rpiDecoder.h"
#include "infraredReceiver.h"


class sensor
{
  public:
    sensor(unsigned char debugInfo);
    bool init();
    bool update();
    unsigned char isVisible();            //Tells if the robot is visible or not (problems with blinking)//Add timer
    unsigned char getLastOneFlagStatus(); //Tells if the robot is in the last position
    unsigned char getDistance();          //Relative distance between the robots
    bool getLeavingFlagStatus();          //The robot in front is leaving
    char getDirection();                  //Relative direction of the robots
    char getOrientation();                //Orientation of the robot in front (sic.)
    
  private:
    unsigned char _debugInfo;             //0 both 1 primary only 2 secondary only
    float _distance;
    infraredDirection _myDirectionSensor;
    flags _mySolarFlag;
    rpiDecoder _myRpiDecoder;
    infraredReceiver _myInfraredReceiver;
    
    
};

#endif
