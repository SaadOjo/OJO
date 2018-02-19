/*
 A signal conditioner library
 Library wrıtten by Syed Saad Saif
 */
#ifndef SIGNAL_CONDITIONER_H
#define SIGNAL_CONDITIONER_H

#include <Arduino.h>

int posSaturate(int nummber, int saturationLevel);
int negSaturate(int nummber, int saturationLevel);
int symmetricSaturate(int nummber, int saturationLevel);
int aSymmetricSaturate(int number, int lowerBound, int upperBound);


#endif
