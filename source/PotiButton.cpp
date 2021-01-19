#include "PotiButton.h"


void PotiButton::changeSelection() {
	this->_potiValue = analogRead(this->_potiPin);
	int range = this->_potiMaxValue / this->_numOfRanges;
	if (this->_potiValue != this->_previousPotiValue) {
		if (this->_potiValue < range) {
			this->_selectedOption = MenuItem::FIRST;

		}
		if (this->_potiValue > 300 && this->_potiValue < range * 2) {
			this->_selectedOption = MenuItem::SECOND;

		}
		else if (this->_potiValue > range * 2) {
			this->_selectedOption = MenuItem::THIRD;
		}

	}
	this->_previousPotiValue = this->_potiValue;
}


int PotiButton::getSelectedOption()
{
	return this->_selectedOption;
}


