/*
 A custom library written for flag transmission
 Library wrıtten by Abdullah Aslam
 */
#ifndef FLAGS_TRANSMITTER_H
#define FLAGS_TRANSMITTER_H

#include <Arduino.h>
#include "infraredTransmitter.h"
class flagsTransmitter
{
  public:
    flagsTransmitter(unsigned char laser_pin, unsigned char sevenSegment_pin);
    bool init();
    void setLeaveSignal(bool state);
    void setLastSignal(bool state);
    void transmit();
    void clearFlags();
   
  private:
    unsigned char _laser_pin, _sevenSegment_pin;
    infraredTransmitter _myTransmitter;
};

#endif
