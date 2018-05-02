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
    unsigned char noOfData = 0;
    unsigned char _pointer;
    unsigned char _averages;
    int _array[MAX_ARRAY_SIZE];
    int _arrayAverage();
    unsigned char _circularIncrement(unsigned char num);
    //float filter[5] = {0.0341, 0.0670, 0.1316, 0.2588, 0.5087};
    float filter[5] = {0.0667,    0.1333,    0.2000,    0.2667,    0.3333};

    

};

#endif
