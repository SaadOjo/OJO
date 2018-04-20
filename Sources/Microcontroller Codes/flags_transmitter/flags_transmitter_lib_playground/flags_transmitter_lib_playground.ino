#include "flagsTransmitter.h"

flagsTransmitter myFlagsTransmitter(4, 7);


void setup()
{
  Serial.begin(115200);
  myFlagsTransmitter.init();

  myFlagsTransmitter.setLeaveSignal(LOW);
  myFlagsTransmitter.setLastSignal(HIGH);
  //myFlagsTransmitter.clearFlags();

}

void loop()
{

  myFlagsTransmitter.transmit();

}

