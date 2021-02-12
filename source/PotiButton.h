
#ifndef POTIBUTTON_H
#define POTIBUTTON_H

#include "MenuItem.h"
#include "Button.h"
class PotiButton :
	public Button
{
private:
	int _selectedOption = 0;
	int _potiValue = 0;
	int _previousPotiValue = 0;
	int _potiPin = 0;
	int _potiMaxValue = 0;
	int _numOfRanges = 0;

public:
	PotiButton() {};

	PotiButton(int inputPin, int buttonState, int lastButtonState, long debounceDelay, int potiPin, int potiMaxValue, int numOfRanges) :
		Button(inputPin, buttonState, lastButtonState, debounceDelay), _potiPin(potiPin), _potiMaxValue(potiMaxValue), _numOfRanges(numOfRanges) {};

	void changeSelection();
	int getSelectedOption();
};


#endif
