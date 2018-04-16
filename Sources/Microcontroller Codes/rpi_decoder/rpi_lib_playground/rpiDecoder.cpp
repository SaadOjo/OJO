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
    char myChar;
    int myNum;
  
    //Check if buffer is empty
    if (Serial.available() > 0) 
    {
        myChar = Serial.read();
        if(myChar == '$')
        {
          dataStarted = true;//cond?
          Serial.println();
        }
        else if(dataStarted)
        {
        if((myChar == ',' || myChar == '&'))
        { 

          //Move Code Here
          shortBuffer[shortBufferByteNo+1] = '\0';
          //Serial.println(shortBuffer);
          myNum = atoi(shortBuffer);
          //Serial.println(myNum);
          //Serial.println(dataFieldNo);
          //Clear Buffer
          for (int j=0;j<BUFFER_SIZE;j++)
          {
           *(shortBuffer + j) = 0; 
          }
          //Serial.print(shortBuffer);
          //Serial.println(myNum);

          switch(dataFieldNo)
          {
            case 0:
              _distance = myNum;
              break;
            case 1:
              _direction = myNum;
              break;
            case 2:
              _orientation = myNum;
              break;
            case 3:
              _leavingFlagState = myNum;
              break;
          }

          dataFieldNo++;
          shortBufferByteNo = 0; 

          if(myChar == '&')
          {
            retBool = true;
            dataStarted = false;
            dataFieldNo = 0;
          }
        }
        else 
        {
          shortBuffer[shortBufferByteNo] = myChar;
          //Serial.println(shortBufferByteNo);
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

char rpiDecoder::getOrientation()
{
  return _orientation;
}

bool rpiDecoder::getLeavingFlagStatus()
{
  return _leavingFlagState;
}


