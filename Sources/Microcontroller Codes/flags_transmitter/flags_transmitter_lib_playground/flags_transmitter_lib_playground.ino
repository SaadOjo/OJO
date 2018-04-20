#include "flagsTransmitter.h"

flagsTransmitter myFlagsTransmitter(2, 3);


void setup()
{
  Serial.begin(115200);
  myFlagsTransmitter.init();

  myFlagsTransmitter.setLeaveSignal(LOW);
  myFlagsTransmitter.setLastSignal(HIGH);
}

void loop()
{

  myFlagsTransmitter.transmit();

}

