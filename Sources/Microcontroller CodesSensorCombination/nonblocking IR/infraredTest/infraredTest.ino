#include "infraredTransmitter.h"
#include "infraredReciever.h"

infraredReciever myReciever(2);
infraredTransmitter myTransmitter(9);

void setup()
{
  Serial.begin(115200);
  myReciever.init();
  myTransmitter.init();
  myTransmitter.setSignalIdentity(2);
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
  myTransmitter.transmit();
  delay(20);
  
}

