#include "button.h"
#define sButton  8

void setup() {
 pinMode(sButton, INPUT);
 digitalWrite(sButton, LOW);
 Serial.begin(115200);
}

void loop() {
   if(checkButton(sButton)){
    Serial.println("On");
   }
   else{
    Serial.println("Off");
   }
}
