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

//Serial.println(edge);

  if(!edge)
  {
  }
  
  else 
  {
    if((edge == 1)&&(lastEdgeType == -1))
    {
      edgeDetected = true;
    }

    lastEdgeType = edge;
  }
  
 return edgeDetected;
}

int remoteDecoder::decode(){
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
