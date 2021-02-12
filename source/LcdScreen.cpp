#include "LcdScreen.h"


void LcdScreen::updateMenu(int state, String firstLine, String secondLine)
{
	if (state != this->_lastState) {
		this->_lcd->clear();
		this->_lcd->setCursor(0, 0); // first row, first character
		this->_lcd->print(firstLine);
		this->_lcd->setCursor(0, 1); // second row, first character
		this->_lcd->print(secondLine);
		this->_lastState = state;
	}
}

void LcdScreen::clearRow(int row)
{
	this->_lcd->setCursor(0, row);
	for (int i = 0; i < this->_displayChars; i++) {
		this->_lcd->print(" ");
	}
}

void LcdScreen::updateSelectableOptions(int state, int option)
{
	if (option != this->_lastSelectedOption) {
		this->clearRow(1);
		this->_lcd->setCursor(0, 1);
		if (state == RoboStates::STATE_CHOOSEDIFFICULTY) {								//TODO change hardcoded number
			this->_lcd->print(_difficulty[option]);
		}
		else {
			this->_lcd->print(_playorder[option]);
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
