#include "average.h"

average myAverage(10);

void setup() {
Serial.begin(115200);
int avg = myAverage.getAverage();
Serial.println(String("Average: ") + avg);

myAverage.addData(10);
myAverage.addData(9);
myAverage.addData(10);
myAverage.addData(9);
myAverage.addData(10);
myAverage.addData(9);
myAverage.addData(10);
myAverage.addData(9);
myAverage.addData(10);
myAverage.addData(9);

avg = myAverage.getAverage();
Serial.println(String("Average 2: ") + avg);



}

void loop() {
 
  delay(100);
}
