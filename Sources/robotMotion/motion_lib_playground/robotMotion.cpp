/*
 A custom library written for wireless lvdt LCD display
 Library wrıtten by Syed Saad Saif
 */
#include "robotMotion.h"

robotMotion::robotMotion(int motor_1, int motor_2)
{
  _motor_1 = motor_1;
  _motor_2 = motor_2; 
}

bool robotMotion::init()
{
  pinMode(_motor_1,OUTPUT);
  pinMode(_motor_2,OUTPUT);
}

bool robotMotion::setDirection(short int direction) // -100 to 100
{
 _direction = direction; 
}

bool robotMotion::setSpeed(unsigned short int speed)
{
_speed = speed;
}
bool robotMotion::run()
{
  //also consider direction
  int satDirection = symmetricSaturate(_direction,100);
  int leftSpeed;
  int rightSpeed;
  if(satDirection>0)//turn Right
  {
    leftSpeed = _speed;
    rightSpeed = (_speed*(100 - satDirection))/100;
  }
  else              //turn right
  {
    satDirection = -satDirection;
    rightSpeed = _speed;
    leftSpeed = (_speed*(100 - satDirection))/100;//I know that we can remove - satDirection and change the minus to plus. Don't be such a smart ass. It is done like this for code symmetry.
  }
  int calLeft = (leftSpeed*_leftCalibrationFactor)/100; //for debugging. use directly
  int calRight = (rightSpeed*_rightCalibrationFactor)/100; 
  //Serial.println(String("Left Speed: " + String(calLeft) + ",Right speed: " + String(calRight) ));
  runLeft(calLeft);
  runRight(calRight);
}
bool robotMotion::runLeft(unsigned short int speed)
{
  int satSpeed = posSaturate(speed,100);
  analogWrite( _motor_1, (satSpeed*255)/100);
}

bool robotMotion::runRight(unsigned short int speed)
{
  int satSpeed = posSaturate(speed,100);
  analogWrite( _motor_2, (satSpeed*255)/100);
}

