#include <infraredReceiver.h>

infraredReceiver myReceiver(9);

void setup()
{
  Serial.begin(115200);
  myReceiver.init();
}

void loop()
{
  switch(myReceiver.detect())
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

