#include "Ultrasonic.h"

Ultrasonic ultrasonic(8, 9, 10000UL);
Ultrasonic ultrasonic2(10, 11, 10000UL);
Ultrasonic ultrasonic3(12, 13, 10000UL);


void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Right Sensor : ");
  Serial.println(ultrasonic.distanceRead());
  Serial.print(" Back Sensor : ");
  Serial.println(ultrasonic2.distanceRead());
  Serial.print("Left Sensor : ");
  Serial.println(ultrasonic3.distanceRead());
  delay(1000);
}
