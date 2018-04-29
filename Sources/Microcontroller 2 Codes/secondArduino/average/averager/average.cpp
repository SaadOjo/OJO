/*
 Averaging lib
 */
#include "average.h"

average::average(unsigned char averages)
{
  _averages = averages;

  if(_averages > MAX_ARRAY_SIZE)
  {
    _averages = MAX_ARRAY_SIZE;
  }
}

void average::addData(int data)
{ 
  *(_array + _pointer) = data;
  _pointer = _circularIncrement(_pointer);
  
}

int average::getAverage()
{
  return _arrayAverage();
}
unsigned char average::_circularIncrement(unsigned char num)
{
  num++;
  if(num >= _averages)
  {
    num = 0;
  }

  return num;
  
}

int average::_arrayAverage()
{
  int localAverage = 0;
  unsigned char localPointer = _circularIncrement(_pointer);
  
  for(int i = 0; i<_averages ;i++)
  {
    Serial.println(localAverage);
    localAverage += *(_array + localPointer);
    localPointer = _circularIncrement(localPointer);
  }

  return localAverage/_averages;
}

