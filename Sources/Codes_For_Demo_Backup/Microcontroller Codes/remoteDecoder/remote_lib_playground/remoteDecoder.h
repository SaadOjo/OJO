/*
 A custom library written for IR distance sensor
 Library wrıtten by Syed Saad Saif
 */
#ifndef REMOTE_DECODER_H
#define REMOTE_DECODER_H

#define DECODE_TIMEOUT 60000

#define ZERO_PULSE_MIN 300
#define ZERO_PULSE_MAX 600

#define ONE_PULSE_MIN 1000
#define ONE_PULSE_MAX 2000

#include <Arduino.h>

class remoteDecoder
{
  public:
    remoteDecoder(int pin);
    bool init();
    bool detectPulse();
    unsigned int decode();

  private:
    short int detectEdge();
    bool _pulse;
    int _pin;
    bool lastEdgeType;
    bool edgeType;
    bool lastLevel = true;
    bool level = true;
   
    
};

void remoteISR(){

_pulse = true;

}

#endif
