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
  bool  retBool = false; 
  bool dataStarted = false;
  unsigned char dataFieldNo = 0;
  char buffer[BUFFER_SIZE];
  char shortBuffer[4];
  char shortBufferByteNo;
  char myNum;
  int i = 0;

  //Check if buffer is empty
  if (Serial.available() > 0) 
  {
    if(i<BUFFER_SIZE)
    {
      buffer[i] = Serial.read();
      Serial.println(buffer[i],DEC);
      i++;
    }
  }

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
        if(buffer[i] == '&')
        {
          retBool = true;
        }
        else
        {
          //Move Code Here
        }
        
        shortBufferByteNo++;
        shortBuffer[shortBufferByteNo+1] = '\0';
        myNum = atoi(shortBuffer);
        Serial.print(shortBuffer);
        Serial.println(myNum);

        dataFieldNo++;
        shortBufferByteNo = 0;

        switch(dataFieldNo)
        {
          case 0:
            _distance = myNum;
            break;
            _direction = myNum;
          case 1:
            _orientation = myNum;
            break;
          case 2:
            _leavingFlagState = myNum;
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

  return retBool; 
   
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


