/*
 A custom library written for wireless lvdt LCD display
 Library wrıtten by Syed Saad Saif
 */
#include "robotMotion.h"

robotMotion::robotMotion(int motor_1_in_1, int motor_1_in_2, int motor_2_in_1, int motor_2_in_2)
{
  _motor_1_in_1 = motor_1_in_1;
  _motor_1_in_2 = motor_1_in_2; 
  _motor_2_in_1 = motor_2_in_1;
  _motor_2_in_2 = motor_2_in_2;
}

bool robotMotion::init()
{
  pinMode(_motor_1_in_1,OUTPUT);
  pinMode(_motor_1_in_2,OUTPUT);
  pinMode(_motor_2_in_1,OUTPUT);
  pinMode(_motor_2_in_2,OUTPUT);
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
  satDirection = symmetricSaturation(_direction,100);
  int leftSpeed;
  int rightSpeed;
  if(satDirection>0)//turn Right
  {
    leftSpeed = 100;
    rightSpeed = 100 - satDirection;
  }
  else              //turn right
  {
    satDirection = -satDirection;
    leftSpeed = 100 - satDirection; //I know that we can remove - satDirection and change the minus to plus. Don't be such a smart ass. It is done like this for code symmetry.
    rightSpeed = 100;
  }
  
  runLeft(leftSpeed*_leftCalibrationFactor);
  runRight(rightSpeed*_rightCalibrationFactor);
}
bool robotMotion::runLeft(unsigned short int speed)
{
  int satSpeed = posSaturate(speed,100);
  analogWrite( _motor_1_in_1, (satSpeed*128)/100);
  analogWrite( _motor_1_in_2, ((satSpeed-100)*128)/100);
}

bool robotMotion::runRight(unsigned short int speed)
{
  int satSpeed = posSaturate(speed,100);
  int satSpeed = posSaturate(speed,100);
  analogWrite( _motor_1_in_1, (satSpeed*128)/100);
  analogWrite( _motor_1_in_2, ((satSpeed-100)*128)/100);
}

