/*
12C reciever and decoder
 */
#include "arduinoReceiverDecoder.h"

arduinoReceiverDecoder::arduinoReceiverDecoder(unsigned char slaveAddress)
{
  _slaveAddress = slaveAddress;
  Wire.begin(slaveAddress);
  Wire.onReceive(_receiveEvent);
}

unsigned char arduinoReceiverDecoder::getRemoteCommand()
{
  //reset to default
  //reset of read
}
unsigned char arduinoReceiverDecoder::getAvoidInfo()
{
  //reset to default
  //reset on read
}
bool arduinoReceiverDecoder::getIfLastInLine()
{
  
}

static void arduinoReceiverDecoder::_receiveEvent(int howMany)
{
  byte b;
  byte lastRobot,remoteInfo,avoidInfo;
  if(Wire.available() != 0)
  {
     for(int i = 0; i<howMany; i++) 
     { 
        b = Wire.read();
        Serial.println(b,HEX);
        lastRobot = b >> 7;
        remoteInfo = (b & 0b01111111) >> 4;
        avoidInfo = b & 0b00001111;

        if(lastRobot) //Kinda Redundant
        {
          _isLastRobotState = true;
        }
        else
        {
          _isLastRobotState = false;
        }

        switch (remoteInfo)//Intentionally Redundant
        {
          case 0b1:
            _remoteInfo = 1;
            break;
          case 0b10:
            _remoteInfo = 2;
          //go left
            break;
          case 0b11:
            _remoteInfo = 3;
          //go right
            break;
        }
        switch (avoidInfo) 
        {
          case 0b1:
            _avoidInfo = 1;
            break;
          case 0b10:
            _avoidInfo = 2;
          //go left
            break;
          case 0b11:
            _avoidInfo = 3;
          //go right
            break;
        }
    } 
  }
}


