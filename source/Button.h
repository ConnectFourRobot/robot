#ifndef BUTTON_H
#define BUTTON_H
#define LOW 0x0
#include "Arduino.h"
class Button {

protected:
	int _buttonPin = 8;
	int _buttonState = LOW;			// current value from input pin
	int _lastButtonState = LOW;		// previous value from input pin

	unsigned long _lastDebounceTime = 0;		// last time the pin was toggled
	long _debounceDelay = 50;		// debounce time

public:

	Button() {};
	Button(int inputPin, int buttonState) : _buttonPin(inputPin), _buttonState(buttonState) {
		pinMode(inputPin, INPUT);
	};
	Button(int inputPin, int buttonState, int lastButtonState) : _buttonPin(inputPin), _buttonState(buttonState), _lastButtonState(lastButtonState) {
		pinMode(inputPin, INPUT);
	};
	Button(int inputPin, int buttonState, int lastButtonState, long debounceDelay) : _buttonPin(inputPin), _buttonState(buttonState), _lastButtonState(lastButtonState), _debounceDelay(debounceDelay) {
		pinMode(inputPin, INPUT);
	};

	//Check the button state
	bool buttonPressed();
};


#endif