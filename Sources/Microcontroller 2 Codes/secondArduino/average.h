/*
 A custom library written for IR distance sensor
 Library wrıtten by Syed Saad Saif
 */
#ifndef AVERAGE_H
#define AVERAGE_H

#include <Arduino.h>

#define MAX_ARRAY_SIZE 10

class average
{
  public:
    average(unsigned char averages);
    int getAverage();
    void addData(int data);
  private:
    unsigned char _pointer;
    unsigned char _averages;
    int _array[MAX_ARRAY_SIZE];
    int _arrayAverage();
    unsigned char _circularIncrement(unsigned char num);
};

#endif
