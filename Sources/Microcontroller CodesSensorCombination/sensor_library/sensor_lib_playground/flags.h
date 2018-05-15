/*
 A custom library written for flags
 Library wrıtten by Syed Saad Saif & Bulut Ulukapi
 */
#ifndef FLAGS_H
#define FLAGS_H

#include <Arduino.h>

class flags
{
  public:
    flags(unsigned char solarPin_Left, unsigned char solarPin_Right);
    bool init();
    bool update();
    unsigned char getSolarLastOneFlag();
  private:

    unsigned char _solarPin_Left, _solarPin_Right;
    bool _solarPin_Left_State, _solarPin_Right_State; 
};

#endif
