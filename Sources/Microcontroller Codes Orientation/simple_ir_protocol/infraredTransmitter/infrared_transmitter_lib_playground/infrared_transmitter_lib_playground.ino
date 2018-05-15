#include "infraredTransmitter.h"

infraredTransmitter myTransmitter(9);

void setup()
{
  Serial.begin(115200);
  myTransmitter.init();
  myTransmitter.setSignalIdentity(1);
}

void loop()
{
  myTransmitter.transmit();
  delay(20);
  
}

