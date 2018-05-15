/*
 A custom library written for flag transmission
 Library wrıtten by Abdullah Aslam
 */
#include "flagsTransmitter.h"
flagsTransmitter::flagsTransmitter(unsigned char laser_pin, unsigned char sevenSegment_pin): _myTransmitter(10)
{
  _laser_pin = laser_pin;
  _sevenSegment_pin = sevenSegment_pin;
  
 
}

bool flagsTransmitter::init(){
  //Analog declaration
  pinMode(_laser_pin,OUTPUT);
  pinMode(_sevenSegment_pin,OUTPUT);
  _myTransmitter.init();


}

void flagsTransmitter::transmit()
{
  _myTransmitter.transmit();
}


void flagsTransmitter::setLeaveSignal(bool state)
{
  digitalWrite(_sevenSegment_pin, state);
  _myTransmitter.setSignalIdentity(1);
  //add other lib
}

void flagsTransmitter::setLastSignal(bool state)
{
  digitalWrite(_laser_pin, state);
  _myTransmitter.setSignalIdentity(2);

  //add other lib
}

void flagsTransmitter::clearFlags()
{
  digitalWrite(_laser_pin, LOW);
  digitalWrite(_sevenSegment_pin, LOW);
  _myTransmitter.alwaysOn();


  //add other lib
}
