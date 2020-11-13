#ifndef POTIBUTTON_H
#define POTIBUTTON_H


#include "Button.h"
class PotiButton :
    public Button
{
	private:
	int _selectedOption = 0;
	int _potiValue = 0;
	int _previousPotiValue = 0;


public:
    PotiButton() {};
	PotiButton(int inputPin, int buttonState) : Button(inputPin, buttonState){};
	PotiButton(int inputPin, int buttonState, int lastButtonState) : Button(inputPin, buttonState, lastButtonState){};
	PotiButton(int inputPin, int buttonState, int lastButtonState, long debounceDelay) : Button(inputPin, buttonState, lastButtonState, debounceDelay){};

	void changeSelection();
	int getSelectedOption();
};


#endif
