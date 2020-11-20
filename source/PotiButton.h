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
	int _potiRanges[3] = { 344, 688, 1024 };
public:
	PotiButton() {};
	PotiButton(int inputPin, int buttonState, int potiPin) : Button(inputPin, buttonState), _potiPin(potiPin) {};
	PotiButton(int inputPin, int buttonState, int lastButtonState, int potiPin) : Button(inputPin, buttonState, lastButtonState), _potiPin(potiPin) {};
	PotiButton(int inputPin, int buttonState, int lastButtonState, long debounceDelay, int potiPin) : Button(inputPin, buttonState, lastButtonState, debounceDelay), _potiPin(potiPin) {};

	void changeSelection();
	int getSelectedOption();
	void setPotiRanges(int firstSection, int secondSection, int thirdSection);
};


#endif
