#include "state.h"
#include "Arduino.h"

int buttonState = LOW;
int lastButtonState =  LOW;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

int checkButton(int pinButton){
  int reading = digitalRead(pinButton);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    
    if (reading != buttonState) {
      buttonState = reading;
    }
  }
  lastButtonState = reading;
  return buttonState;
}
