/*
 A custom library written for IR distance sensor
 Library wrıtten by Syed Saad Saif
 */
#ifndef REMOTE_DECODER_H
#define REMOTE_DECODER_H

#include <Arduino.h>

class remoteDecoder
{
  public:
    remoteDecoder(int pin);
    bool init();
    bool detectPulse();
    int decode();

  private:
    short int  detectEdge();
    int _pin;
    bool lastEdgeType;
    bool edgeType;
    bool lastLevel = true;
    bool level = true;
    
};

#endif
