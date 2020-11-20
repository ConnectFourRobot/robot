#include "LcdScreen.h"


void LcdScreen::updateMenu(int state, int sCursor)
{	
	if (state != this->_lastState){
		this->_lcd->clear();
		this->_lcd->setCursor(0, sCursor);
		this->_lcd->print(this->messages[state]);
		this->_lastState = state;
	}
}

void LcdScreen::clearRow(int row)
{
	this->_lcd->setCursor(0, row);
	for (int i = 0; i < 16; i++) {
		this->_lcd->print(" ");
	}
}

void LcdScreen::updateSelectableOptions(int state, int option)
{
	if (option != this->_lastSelectedOption) {
		this->clearRow(1);
		this->_lcd->setCursor(0, 1);
		if (state == 2) {								//TODO change hardcoded number
			this->_lcd->print(Difficulty[option]);
		}
		else{
			this->_lcd->print(Playorder[option]);
		}
		this->_lastSelectedOption = option;
	}
}

void LcdScreen::initDisplay()
{
	this->_lcd->init();
	this->_lcd->backlight();
}

void LcdScreen::resetLastSelectedOption()
{
	this->_lastSelectedOption = -1;
}

