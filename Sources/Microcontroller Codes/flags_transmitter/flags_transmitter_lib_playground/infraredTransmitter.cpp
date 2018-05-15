/*
 Protocol XX minimal resource, non blocking IR transmitter library
 Library written by Syed Saad Saif

License Information:

Copyright 2018 Syed Saad Saif

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Signal Identities:

____Signal Identifier__|__Signal Description____|__Signal Parameters__|
            1          |     Type A
            2          |     Type B
 
 Library Limitations:

 The signal can only be transmitted on PINS D9 or D10
 
 */
#include "infraredTransmitter.h"

infraredTransmitter::infraredTransmitter(int pin)
{
  //You can only use pins D9 or D10
  _pin = pin;
  pinMode(_pin,OUTPUT);
 
}

bool infraredTransmitter::init(){
//Set LED Carrier Frequency
TCCR1B = TCCR1B & B11111000 | B00000001;    // set timer 1 divisor to     1 for PWM frequency of 31372.55 Hz
}

bool infraredTransmitter::setSignalIdentity(unsigned char signalIdentity)
{
  _signalIdentity =  signalIdentity;
  return true;
}

unsigned char infraredTransmitter::getSignalIdentity()
{
  return _signalIdentity;
}
bool infraredTransmitter::transmit()
{
  //Serial.println(_pinState);
  unsigned int timeBetweenSwitch;
  switch(_signalIdentity)
  {
    case 1:
      timeBetweenSwitch = TYPE_A_TIME;
      break;
    case 2:
      timeBetweenSwitch = TYPE_B_TIME;
      break;
  }
  unsigned long int currentTime = millis();
  //Serial.println(currentTime);
  if((currentTime -  _lastEventChangeTime) > timeBetweenSwitch)
  {
    //Serial.println("Toggle");
    togglePwm();
    _lastEventChangeTime = currentTime;
  }
  

}
bool infraredTransmitter::alwaysOn() //Call once Check if you can return back from always on 
{
  digitalWrite(_pin, HIGH);
  return true;
}

bool infraredTransmitter::togglePwm()
{
  if(_pinState)
  {
    analogWrite(_pin, 0);
    _pinState = false;
  }
  else
  {
    analogWrite(_pin, 200);
    _pinState = true;
  }
}
