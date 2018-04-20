/*
 A custom library written for flag transmission
 Library wrıtten by Abdullah Aslam
 */
#include "flagsTransmitter.h"
flagsTransmitter::flagsTransmitter(unsigned char laser_pin, unsigned char sevenSegment_pin)
{
  _laser_pin = laser_pin;
  _sevenSegment_pin = sevenSegment_pin;
  
 
}

bool flagsTransmitter::init(){
//Analog declaration
pinMode(_laser_pin,OUTPUT);
pinMode(_sevenSegment_pin,OUTPUT);

}

void flagsTransmitter::transmit()
{
  

}


void flagsTransmitter::setLeaveSignal(bool state)
{
  digitalWrite(_sevenSegment_pin, state);
  //add other lib
}

void flagsTransmitter::setLastSignal(bool state)
{
  digitalWrite(_laser_pin, state);
  //add other lib
}

void flagsTransmitter::clearFlags()
{
  digitalWrite(_laser_pin, LOW);
  digitalWrite(_sevenSegment_pin, LOW);
  //add other lib
}
