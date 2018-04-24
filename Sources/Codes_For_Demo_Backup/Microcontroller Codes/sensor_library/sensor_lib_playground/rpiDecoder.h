/*
 A custom library written for decoding raspberry pi sensor
 Library wrıtten by Syed Saad Saif
 */
#ifndef RPI_DECODER_H
#define RPI_DECODER_H

#define BUFFER_SIZE 6

#include <Arduino.h>

class rpiDecoder
{
  public:
    rpiDecoder();
    bool update();
    bool getLeavingFlagStatus();
    unsigned char getDistance();
    char getDirection();
    char getOrientation();

  private:
    unsigned int shortBufferByteNo;
    char shortBuffer[BUFFER_SIZE];
    unsigned char dataFieldNo = 0;
    bool dataStarted = false;
    int i = 0;

    
    bool _leavingFlagState;
    unsigned char _orientation;
    unsigned char _distance;
    char _direction;
};

#endif
