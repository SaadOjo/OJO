/*
 A signal conditioner library
 Library wrıtten by Syed Saad Saif
 */
#include "signalConditioner.h"

int posSaturate(int nummber, int saturationLevel)
{

  number = aSymmetricSaturate(number, 0, saturationLevel)

  return number;
}

int negSaturate(int nummber, int saturationLevel)
{

  number = aSymmetricSaturate(number, saturationLevel, 0)

  return number;
}

int symmetricSaturate(int nummber, int saturationLevel)
{

  number = aSymmetricSaturate(number, saturationLevel, saturationLevel)

  return number;
}

int aSymmetricSaturate(int number, int lowerBound, int upperBound)
{
if (number > upperBound)
  {
    number = upperBound;
  }
  else if(number < lowerBound)
  {
    number = lowerBound;
  }
  return number;
}


