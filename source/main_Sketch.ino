#include "Button.h"

void setup() {
 pinMode(sButton, INPUT);
 digitalWrite(sButton, LOW);
 Serial.begin(115200);
}

void loop() {
   Button();
}