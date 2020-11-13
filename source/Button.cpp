#include "Button.h"


bool Button::buttonPressed()
{
	int newButtonState = digitalRead(this->_buttonPin);

	// update lastDebounceTime
	if (newButtonState != this->_lastButtonState) {
		this->_lastDebounceTime = millis();
	}

	if ((millis() - this->_lastDebounceTime) > this->_debounceDelay) {
		
		if (newButtonState != this->_buttonState) {
			this->_buttonState = newButtonState;

			return true;
		}
	}
	this->_lastButtonState = newButtonState;
	return false;
} 

