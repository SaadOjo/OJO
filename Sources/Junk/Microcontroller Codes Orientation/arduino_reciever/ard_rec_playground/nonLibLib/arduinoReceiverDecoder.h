/*
12C reciever and decoder
 */
#ifndef ARDUINO_RECIEVER_DECODER_H
#define ARDUINO_RECIEVER_DECODER_H

#include <Arduino.h>
#include <Wire.h>

class arduinoReceiverDecoder
{
  public:
    arduinoReceiverDecoder(unsigned char slaveAddress);
    unsigned char getRemoteCommand(); //reset on reading
    unsigned char getAvoidInfo(); //reset on reading
    bool getIfLastInLine();
    void validate();

  private:
    unsigned char _slaveAddress;
    static void _receiveEvent(int howMany);

   static bool _isLastRobotState;
   static unsigned char _avoidInfo;
   static unsigned char _remoteInfo;
    //unsigned long int _lastUpdateTime;

};

#endif
