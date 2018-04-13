  /*
 A custom library written for decoding raspberry pi information
 Library wrıtten by Syed Saad Saif
 */
#include "rpiDecoder.h"

rpiDecoder::rpiDecoder()
{ 

}

bool rpiDecoder::update()
{
  //Parse here

    /*
   Data Format
   Distance, Direction,Orientation,Flag
   $100,-100,-100,0&
   */
  bool dataStarted = false;
  unsigned char dataFieldNo = 0;
  char buffer[BUFFER_SIZE];
  char shortBuffer[4];
  char shortBufferByteNo;
  for(int i = 0;i<BUFFER_SIZE;i++)
  {
    if(buffer[i] == '$')
    {
      dataStarted = true;
    }
    else
    {
      if(buffer[i] == ',' || buffer[i] == '&')
      {
        dataFieldNo++;
        shortBufferByteNo = 0;

        switch(dataFieldNo)
        {
          case 0:
            _distance = _toNumber(shortBuffer);
            break;
            _direction = _toNumber(shortBuffer);
          case 1:
            _orientation = _toNumber(shortBuffer);
            break;
          case 2:
            _leavingFlagState = _toNumber(shortBuffer)? 1 : 0 ;
            break;
        }
      }
      else
      {
        shortBuffer[shortBufferByteNo] = buffer[i];
        shortBufferByteNo++;
      }
    } 
  }

   
   
}

char rpiDecoder::getDirection()
{
  return _direction;
}

unsigned char rpiDecoder::getDistance()
{
  return _distance;
}

unsigned char rpiDecoder::getOrientation()
{
  return _orientation;
}

bool rpiDecoder::getLeavingFlagStatus()
{
  return _leavingFlagState;
}

char rpiDecoder::_toNumber(char buff[])
{
  char number;
  return number;

}


