#include "infraredReciever.h"

infraredReciever myReciever(9);

void setup()
{
  Serial.begin(115200);
  myReciever.init();
}

void loop()
{
  switch(myReciever.detect())
  {
    case 1:
      Serial.println("Signal Type A detected!");
      break;
    case 2:
      Serial.println("Signal Type B detected!");
      break;
  }
  
  delay(20);
  
}

