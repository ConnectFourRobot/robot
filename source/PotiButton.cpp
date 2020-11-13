#include "PotiButton.h"


void PotiButton::changeSelection(){
	this->_potiValue = analogRead(0);
	if (this->_potiValue != this->_previousPotiValue) {
		if (this->_potiValue < 344) {
			this->_selectedOption = 0;
			
		}
		if (this->_potiValue > 344 && this->_potiValue < 688) {
			this->_selectedOption = 1;

		}
		if (this->_potiValue > 688) {
			this->_selectedOption = 2;
		}
		
	}
	this->_previousPotiValue = this->_potiValue;
}


int PotiButton::getSelectedOption()
{
	return this->_selectedOption;
}
