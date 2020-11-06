#include "state.h"
#include "Arduino.h"
#define sButton  8

short trigger = 0;

void Button(){
  while(1){
    delay(50);
    if(digitalRead(sButton)== 0){
      trigger = digitalRead(sButton);
    }
    if(digitalRead(sButton)==1 && trigger ==0){
      trigger = digitalRead(sButton);
      if(eventIsSet(Q2)){
        clearEvent(Q2);
        Serial.println("Aus");
      }else{
        Serial.println("Ein");
        setEvent(Q2);
      }
    }
  }
}