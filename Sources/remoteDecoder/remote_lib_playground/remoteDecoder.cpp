/*
 A custom library written for IR distance sensor
 Library wrıtten by Syed Saad Saif
 */
#include "remoteDecoder.h"

remoteDecoder::remoteDecoder(int pin)
{
  _pin = pin;
}

bool remoteDecoder::init(){

pinMode(_pin,INPUT);

}

bool remoteDecoder::detectPulse(){
  
bool edgeDetected = false;
short int edge = detectEdge();

if((edge==1)||(edge==-1))
{
    
    if((edge == 1)&&(lastEdgeType == false))
    {
      edgeDetected = true;
    }

    if(edge == 1)
    {
      lastEdgeType = true;
    }
    else
    {
      lastEdgeType = false;
    }
}

 return edgeDetected;
}

unsigned int remoteDecoder::decode(){

  //wait for falling edge
  short int edge; 
  
  bool dataStartDetected = false;
  bool recievedBit;
  
  unsigned int decoded;  
  unsigned long int startTime;
  unsigned long int loopTime;
  unsigned  int risingEdgeTime;
  unsigned  int pulseTime; 
  unsigned char bitNumber = 0;

  startTime =  micros();

   while((loopTime - startTime)< DECODE_TIMEOUT) //Timer to protect against infinte loop
   {
    loopTime = micros();

      edge = detectEdge();

      if(edge)
      {
        if(dataStartDetected = false)             //Improve efficiency. Only runs algorithim when data start is detected
        {
          if(edge == -1)
          {
            dataStartDetected = true;
          }
        }
        else
        { 

          if(edge == 1)
          {
            risingEdgeTime = loopTime;
          }
          else if(edge == -1)
          {
            pulseTime = risingEdgeTime - loopTime;

            if((pulseTime>ZERO_PULSE_MIN)&&(pulseTime<ZERO_PULSE_MAX))
            {
              recievedBit = true;
            }
            else if((pulseTime>ONE_PULSE_MIN)&&(pulseTime<ONE_PULSE_MAX))
            {
              recievedBit = false;
            }
            bitWrite(decoded,bitNumber,recievedBit);
            bitNumber++;

          }

        
          if(edge == 1)
          {
            lastEdgeType = true;
          }
          else if(edge == -1)
          {
            lastEdgeType = false;
          }
        }
      }
      
     
       //Can add delay for stability?
   }


 return decoded;
}

short int remoteDecoder::detectEdge(){
  
  level = digitalRead(_pin);
  short int edge = 0;
  if(level != lastLevel)
  {
    if(level)
    {
      edge = 1;
    }
    else if(level == 0) //Redundant
    {
      edge = -1;
    }
  }
  else
  {
  }
  lastLevel = level;
  return edge;
}
