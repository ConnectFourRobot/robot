#include "PotiButton.h"


void PotiButton::changeSelection() {
	this->_potiValue = analogRead(this->_potiPin);
	if (this->_potiValue != this->_previousPotiValue) {
		if (this->_potiValue < this->_potiRanges[0]) {
			this->_selectedOption = MenuItem::FIRST;

		}
		if (this->_potiValue > this->_potiRanges[0] && this->_potiValue < this->_potiRanges[1]) {
			this->_selectedOption = MenuItem::SECOND;

		}
		if (this->_potiValue > this->_potiRanges[1]) {
			this->_selectedOption = MenuItem::THIRD;
		}

	}
	this->_previousPotiValue = this->_potiValue;
}


int PotiButton::getSelectedOption()
{
	return this->_selectedOption;
}

void PotiButton::setPotiRanges(int firstSection, int secondSection, int thirdSection)
{
	this->_potiRanges[0] = firstSection;
	this->_potiRanges[1] = secondSection;
	this->_potiRanges[2] = thirdSection;
}
