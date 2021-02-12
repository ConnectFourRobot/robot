#include "Button.h"


bool Button::buttonPressed()
{
	int newButtonState = digitalRead(this->_buttonPin);
	unsigned long currentMillis = millis();
	// update lastDebounceTime
	if ((currentMillis - this->_lastDebounceTime) > this->_debounceDelay) {
		this->_lastDebounceTime = currentMillis;

		if (newButtonState != this->_buttonState && newButtonState != this->_lastButtonState) {
			this->_lastButtonState = newButtonState;
			return true;
		}
		else {
			this->_lastButtonState = newButtonState;
			return false;
		}

	}
	else {
		return false;
	}
}

