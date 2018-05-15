#include "flags.h"

flags myFlag(2, 3);


void setup()
{
  Serial.begin(115200);
  myFlag.init();
}

void loop()
{
  myFlag.update();
  Serial.println(myFlag.getSolarLastOneFlag());
  delay(100);
}

