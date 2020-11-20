#ifndef LCDSCREEN_H
#define LCDSCREEN_H

#include "LiquidCrystal_I2C.h"


class LcdScreen
{
private: 
	int _lastState = -1;
	int _state = 0;
	int _lastSelectedOption = 0;
	LiquidCrystal_I2C * _lcd;
	String _messages[10] = { "BOOTING", "READY", "DIFFICULTY", "PLAYORDER" ,"REQUEST", "ANSWER","MOVE" };
	String _difficulty[3] = { "EASY", "MEDIUM","HARD" };
	String _playorder[3] = { "HUMAN", "KI", "RANDOM" };

public: 
	LcdScreen(int i2cAdress, int displayChars, int displayLines) { _lcd = new LiquidCrystal_I2C(i2cAdress, displayChars, displayLines); };
	LcdScreen(int i2cAdress, int displayChars, int displayLines, int lastState, int state) : _lastState(lastState), _state(state) {_lcd = new LiquidCrystal_I2C(i2cAdress, displayChars, displayLines); };

	void updateMenu(int state, int sCursor);
	void clearRow(int row) ;
	void updateSelectableOptions(int state, int option) ;
	void initDisplay();
	void resetLastSelectedOption();
};



#endif
