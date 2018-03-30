/*
 A custom library written for wireless lvdt LCD display
 Library wrıtten by Syed Saad Saif
 */
#include "flags.h"

flags::flags(unsigned char solarPin_Left, unsigned char solarPin_Right)
{
  _solarPin_Left = solarPin_Left;
  _solarPin_Right = solarPin_Right;
  
 
}

bool flags::init(){
//Analog declaration
pinMode(_solarPin_Left,INPUT);
pinMode(_solarPin_Right,INPUT);

}

bool flags::update()
{
  _solarPin_Left_State = digitalRead(_solarPin_Left);
  _solarPin_Right_State = digitalRead(_solarPin_Right);

}

unsigned char flags::getSolarLastOneFlag()
{
  unsigned char status = false;
  if(_solarPin_Left_State^_solarPin_Right_State)
  {
      if(_solarPin_Left_State)
      {
        status = 1;
      }
      else
      {
        status = 2;
          
      }
  }
  
  // 0 is no flag, 1 is left,2 is right 
  return status; 
}


