#ifndef LCDSCREEN_H
#define LCDSCREEN_H

#include "RoboStates.h"
#include "LiquidCrystal_I2C.h"


class LcdScreen
{
private:
	int _lastState = -1;
	int _state = 0;
	int _lastSelectedOption = 0;
	int _displayChars = 0;
	LiquidCrystal_I2C* _lcd;
	String _difficulty[3] = { "EASY", "MEDIUM","HARD" };
	String _playorder[3] = { "HUMAN", "KI", "RANDOM" };

public:
	LcdScreen(int i2cAdress, int displayChars, int displayLines) : _displayChars(displayChars) { _lcd = new LiquidCrystal_I2C(i2cAdress, _displayChars, displayLines); };
	LcdScreen(int i2cAdress, int displayChars, int displayLines, int lastState, int state) : _lastState(lastState), _state(state), _displayChars(displayChars) { _lcd = new LiquidCrystal_I2C(i2cAdress, displayChars, displayLines); };


	void updateMenu(int state, String firstLine, String secondLine = " ");            //update Display only when state is changed
	void clearRow(int row);
	void updateSelectableOptions(int state, int option);
	void initDisplay();
	void resetLastSelectedOption();
};



#endif
