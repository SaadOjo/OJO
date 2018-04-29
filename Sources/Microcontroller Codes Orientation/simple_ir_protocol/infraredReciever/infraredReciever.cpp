/*
 Protocol XX minimal resource, non blocking IR reciever library
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
 
 
 */
#include "infraredReciever.h"

infraredReciever::infraredReciever(int pin)
{
  _pin = pin;
 
}

bool infraredReciever::init(){
}

unsigned char infraredReciever::detect()
{
  bool _pinState = digitalRead(_pin);
  if(_pinState!=_pinLastState)
  {
    unsigned long eventTime = millis();
    if(_pinState)//Rising Edge
    {
      unsigned long offTime = eventTime - _fallingEdgeTime;

      if((offTime > TYPE_A_TIME - TIME_TOLERANCE)&&(offTime < TYPE_A_TIME + TIME_TOLERANCE))
      {
        _signalIdentity = 1;
      }
      else if((offTime > TYPE_B_TIME - TIME_TOLERANCE)&&(offTime < TYPE_B_TIME + TIME_TOLERANCE))
      {
        _signalIdentity = 2;
      }
    }
    else
    {
      _fallingEdgeTime = eventTime;
    }
  }
  else
  {
    _signalIdentity = 0;
  }

  _pinLastState = _pinState;
  return _signalIdentity;
}

