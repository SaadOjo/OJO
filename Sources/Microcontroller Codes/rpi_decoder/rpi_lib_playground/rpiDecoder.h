/*
 A custom library written for decoding raspberry pi sensor
 Library wrıtten by Syed Saad Saif
 */
#ifndef RPI_DECODER_H
#define RPI_DECODER_H

#define BUFFER_SIZE 16

#include <Arduino.h>

class rpiDecoder
{
  public:
    rpiDecoder();
    bool update();
    bool getLeavingFlagStatus();
    unsigned char getDistance();
    char getDirection();
    unsigned char getOrientation();

  private:
    bool _leavingFlagState;
    unsigned char _orientation;
    unsigned char _distance;
    char _direction;
    char _toNumber(char buff[]);
};

#endif
