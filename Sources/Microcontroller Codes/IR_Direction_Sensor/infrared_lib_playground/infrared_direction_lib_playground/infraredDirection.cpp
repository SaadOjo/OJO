/*
 A custom library written IR direction sensor
 Library wrıtten by Syed Saad Saif
 */
#include "infraredDirection.h"

infraredDirection::infraredDirection(int pinLeft, int pinRight)
{
  _pinLeft = pinLeft;
  _pinRight = pinRight;
 
}

bool infraredDirection::init(){
//Analog declaration
}
bool infraredDirection::update(){
//Analog declaration
_rightVoltage = getRightVoltage();
_leftVoltage =  getLeftVoltage();

_maxVoltage = max(_leftVoltage, _rightVoltage);

}
bool infraredDirection::isVisible()
{
  bool visibility = false;
  Serial.println(String("max voltage:") + _maxVoltage);
  if(_maxVoltage > VISIBLE_THRESHOLD)
  {
    visibility = true;
  }
  return visibility;
}

float infraredDirection::getDistance()
{
  float distance = 0;
  float voltageAverage = (_rightVoltage + _leftVoltage)/2;
  distance = 34.48*1/sqrt(voltageAverage);
  return distance;
}

float infraredDirection::getDirection()
{
  _direction = (_rightVoltage - _leftVoltage)*20; //don't need saturation (no scaling required)
  /*
  if(_direction>0)
  {
    _addData(1);
  }
  else
  {
    _addData(-1);
  }
  */
  
  if(_detectSignChange())
  {
    _direction = 70;
  }
/*
  if(_direction<-5)
  {
    _direction = -70;
  }
  else if(_direction>5)
  {
    _direction = 70;
  }
  else
  {
    _direction = 0;
  }
  */
  

  return _direction;
}

float infraredDirection::getLeftVoltage()
{
  _leftCount = analogRead(_pinLeft);
  _leftVoltage = (float)_leftCount*_referenceVoltage/1024;
  return _leftVoltage;
}

float infraredDirection::getRightVoltage() //don't store for values (for optimisation)
{
  _rightCount = analogRead(_pinRight);
  _rightVoltage = (float)_rightCount*_referenceVoltage/1024;
  return _rightVoltage;
}

void infraredDirection::_addData(int data)
{ 
  
  *(_array + _pointer) = data;
  _pointer = _circularIncrement(_pointer);

  if(noOfData<DATA_CONSIDERED)
  {
    noOfData++;
  }
    
}

unsigned char infraredDirection::_circularIncrement(unsigned char num)
{
  num++;
  if(num >= DATA_CONSIDERED)
  {
    num = 0;
  }
}

bool infraredDirection::_detectSignChange()
{
  unsigned char pos = 0;
  unsigned char neg = 0;
  unsigned char localPointer = _circularIncrement(_pointer);
  bool retVal = false;
  
  for(int i = 0; i<DATA_CONSIDERED ;i++)
  {
     if(*(_array + localPointer)>0)
     {
      pos++;
     }
     if(*(_array + localPointer)<0)
     {
      neg++;
     }

   Serial.println(String("Value: ") + *(_array + localPointer) );
   Serial.println(String("LP: ") + localPointer );

    
    localPointer = _circularIncrement(localPointer);
  }

  Serial.println(String("Neg: ") + neg + " ,Pos:" + pos);
  if(pos>0 && neg>0)
  {
    retVal = true;
  }
  
  if(noOfData<DATA_CONSIDERED)
  {
    return 0;
  }
  else
  {
    return retVal;
  }
}


//calibrate using average voltage of sensors
