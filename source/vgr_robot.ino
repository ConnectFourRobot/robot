#define STATE_BOOTING 0
#define STATE_READY 1
#define STATE_CHOOSEDIFFICULTY 2
#define STATE_PLAYORDER 3
#define STATE_REQUEST 4
#define STATE_ANSWER 5
#define STATE_MOVE 6
#define STATE_STOPGAME 7
#define STATE_ENDGAME 8


#include "LcdScreen.h"
#include "Wire.h"
#include "PotiButton.h"


int state;
Button startButton = Button(8, LOW, LOW,  50);
PotiButton poti = PotiButton(9, LOW, LOW, 50);
LcdScreen * screen = new LcdScreen(STATE_BOOTING, STATE_BOOTING);



void setup() {
	Serial.begin(115200);
	state = 0;
	screen->initDisplay();
}


void loop() {

	switch (state) {
		case STATE_BOOTING:
			screen->updateMenu(STATE_BOOTING, 0);
																				//TODO: wait for serial READY Message 
			state = STATE_READY;
			break;
		case STATE_READY:
			screen->updateMenu(STATE_READY, 0);
			if (startButton.buttonPressed()) {
			 state = STATE_CHOOSEDIFFICULTY;
			 screen->resetLastSelectedOption();
			}
			break;
		case STATE_CHOOSEDIFFICULTY: 
			screen->updateMenu(STATE_CHOOSEDIFFICULTY, 0);
			screen->updateSelectableOptions(state, poti.getSelectedOption());
			poti.changeSelection();
			if(poti.buttonPressed()){
				state = STATE_PLAYORDER;
				screen->resetLastSelectedOption();
				int difficulty = poti.getSelectedOption();
			}
			break;
		case STATE_PLAYORDER:
			screen->updateMenu(STATE_PLAYORDER, 0);
			screen->updateSelectableOptions(state,poti.getSelectedOption());
			poti.changeSelection();
			if(poti.buttonPressed()){
				state = STATE_PLAYORDER;
				int playorder = poti.getSelectedOption();
			}
			break;
		case STATE_REQUEST:
			state = STATE_ANSWER;
			break;
		case STATE_ANSWER:
			state = STATE_MOVE;
			break;
		case STATE_MOVE:
			state = STATE_REQUEST;
			break;
		case STATE_STOPGAME:
			state = STATE_ENDGAME;
			break;
		case STATE_ENDGAME:
			state = STATE_READY;
			break;
	}
}
