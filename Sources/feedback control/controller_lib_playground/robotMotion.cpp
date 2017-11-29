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

bool setSpeed()
{
  
}
bool robotMotion::setLeftSpeed(unsigned short int speed)
{
  analogWrite( _motor_1_in_1, speed);
  analogWrite( _motor_1_in_2, 255 - speed);
}

