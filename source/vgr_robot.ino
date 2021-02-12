#include <LiquidCrystal_I2C.h>
#include "LcdScreen.h"
#include "Wire.h"
#include "PotiButton.h"
#include "MessageType.h"
#include "RoboStepper.h"
#include "RoboStates.h"
#include <Servo.h>

typedef struct {       //game settings to choose in the lcd menu
	uint8_t difficulty;
	uint8_t playorder;
}settings;

volatile RoboStates state;                                           //actual state in state machine (switch-case)
MessageType type;                                           //type of the message
const byte interruptPin = 3;                                //arduino pin for interrupt detection
Button endStop = Button(3, LOW);
Button startButton = Button(8, LOW, LOW, 50);               //button to start and stop the game
PotiButton poti = PotiButton(9, LOW, LOW, 50, 0, 693, 3);           //button to select menu option
LcdScreen* screen = new LcdScreen(0x27, 16, 4, RoboStates::STATE_INITIAL, RoboStates::STATE_BOOTING);   // create an lcd screen object
RoboStepper stepper = RoboStepper(550, 175, 100, 100);        //stepper motor for horizontal movement
Servo crawl;                                                //crawl which holds the stone
short servoOpenPosition = 50;
short servoClosedPosition = 10;
short servoPin = 6;
settings GameConfig;


// Forward declarations
void serialInterrupt();
char* getSerialData();
MessageType getMessageType(char* message);
void sendSerialMessage(MessageType SerialMessage, byte payload[] = 0, int size = 0);        // default value if there is no payload to send
uint8_t* getMessagePayload(const char* message);
void sendConfig(uint8_t difficulty, uint8_t  playorder);
void initStepperPosition();

void setup() {
	pinMode(interruptPin, INPUT);
	attachInterrupt(digitalPinToInterrupt(interruptPin), endStopInterruptHandler, RISING);
	Serial.begin(9600);                                   //init serial with baudrate 
	state = RoboStates::STATE_BOOTING;
	screen->initDisplay();
	crawl.attach(servoPin);
	initStepperPosition();
}
void initStepperPosition() {
	crawl.write(servoOpenPosition);
	if (digitalRead(interruptPin) == HIGH) {
		stepper.setHomePositionReached();
	}
	else {
		stepper.goToHomePosition();
		stepper.setRunAllowed(true);
	}
}
void endStopInterruptHandler() {
	static unsigned long last_interrupt_time = 0;
	unsigned long interrupt_time = millis();
	// If interrupts come faster than 200ms, assume it's a bounce and ignore
	if (interrupt_time - last_interrupt_time > 300 && stepper.distanceToGo() < 0)
	{
		stepper.stopMotor(); //stop running stepper
		stepper.setHomePositionReached();   //means, that the home button was pressed by the stepper
		if (state == RoboStates::STATE_WAITING_BROKER) {
			state = RoboStates::STATE_DONE;
		}
	}
	last_interrupt_time = interrupt_time;
}

char* getSerialData() {         //read message from broker (MessageType, size, payload)   
	if (Serial.available() >= 2) {    //check if a serial message occured
		char typeAsize[3];
		Serial.readBytes(typeAsize, 2);
		typeAsize[2] = '\0';

		uint8_t size = typeAsize[1];
		char* serialMessage = (char*)malloc(size + 3);
		if (size > 0) {
			char* payload = (char*)malloc(size + 1);
			Serial.readBytes(payload, size);
			payload[size] = '\0';
			strcpy(serialMessage, typeAsize);
			strcat(serialMessage, payload);
			free(payload);
			return serialMessage;

		}
		else {
			return strcpy(serialMessage, typeAsize);  //concatenate to a single message
		}
	}
	else {
		return NULL;
	}
}

MessageType getMessageType(char* message) {
	return (MessageType)message[0];
}

void sendSerialMessage(MessageType SerialMessage, byte payload[] = 0, int size = 0) {
	char type = SerialMessage;                                          //MessageType
	char* message = (char*)malloc(size + 2);
	message[0] = type;
	message[1] = size;
	if (size > 0) {
		for (int i = 0; i < size; i++) {
			message[i + 2] = payload[i];
		}
	}
	Serial.write(message, size + 2);
	Serial.flush();
	free(message);
}
uint8_t* getMessagePayload(const char* message) {
	int size = message[1];
	uint8_t* payload = (uint8_t*)malloc(size + 1);
	payload[size] = '\0';
	for (int i = 2; i <= 1 + size; i++) {
		payload[i - 2] = message[i];

	}
	return payload;

}



void activeGame(char* message) {
	type = getMessageType(message);
	switch (type) {
		case MessageType::MoveRequest:
		{
			uint8_t* payload = getMessagePayload(message);
			if (payload[0] == PayloadType::HUMAN) {
				screen->updateMenu(RoboStates::STATE_HUMAN_MOVE, "Make your move!");
			}
			else {
				screen->updateMenu(RoboStates::STATE_WAITING_USER, "I am thinking...");
			}
			free(payload);
			break;
		}
		case MessageType::DetectedMove:
		{
			uint8_t* payload = getMessagePayload(message);
			screen->updateMenu(RoboStates::STATE_DETECTED_MOVE, "Detected Move :", (String)(payload[0] + 1));
			free(payload);
			break;
		}
		case MessageType::Move:
		{
			uint8_t* payload = getMessagePayload(message);
			screen->updateMenu(RoboStates::STATE_ROBO_MOVE, "Doing move...", (String)(payload[0] + 1));
			stepper.setHomePositionReached();                                 //called twice (before: in pressedHomeButton()), maybe there is a better solution
			stepper.configureMove(payload[0]);
			free(payload);
			crawl.write(servoClosedPosition);
			delay(2000);                                                      //time for closing servo
			stepper.setRunAllowed(true);
			break;
		}
		case MessageType::Endgame:
		{
			uint8_t* payload = getMessagePayload(message);
			if (payload[0] == PayloadType::HUMAN_ROBOT_INTERACTION) {
				stepper.stopMotor();
				screen->updateMenu(RoboStates::STATE_HUMAN_ROBOT_INTERACTION, "Human-Robot", "Interaction");
				state = RoboStates::STATE_ENDGAME;
				delay(2000);
			}
			if (payload[0] == PayloadType::HUMAN) {
				screen->updateMenu(RoboStates::STATE_ENDGAME, "You won!");
			}
			if (payload[0] == PayloadType::ROBOT) {
				screen->updateMenu(RoboStates::STATE_ENDGAME, "You lost!");
			}
			if (payload[0] == PayloadType::RANDOM) {
				screen->updateMenu(RoboStates::STATE_ENDGAME, "no winner");
			}
			free(payload);
			delay(5000);                      // needed to show end result, alternatively implement press button
			state = RoboStates::STATE_ENDGAME;
			break;
		}
		case MessageType::DispEmpty:
		{
			screen->updateMenu(RoboStates::STATE_DISP_EMPTY, "Refill dispenser", "Press button");
			state = RoboStates::STATE_DISP_EMPTY;
			break;
		}
	}
}




void loop() {
	if (stepper.checkRunAllowed()) {
		stepper.continuousRun();      //move stepper when _runAllowed in stepper true  
		//TODO: check if accelStepper.distanceToGo() initially equals 0. Should step in this function after first move done
		if (stepper.positionReached()) {    // stepper reached the position of the received move
			crawl.write(servoOpenPosition);
			delay(2000);
			stepper.goToHomePosition();
		}
	}


	switch (state) {                            // start with the state machine
		case RoboStates::STATE_BOOTING:
		{
			screen->updateMenu(RoboStates::STATE_BOOTING, "Booting...");
			if (Serial.available() >= 2) {
				char* message = getSerialData();
				if (getMessageType(message) == MessageType::Ready) {
					state = RoboStates::STATE_READY;
				}
				free(message);
			}
			break;
		}
		case RoboStates::STATE_READY:
		{
			screen->updateMenu(RoboStates::STATE_READY, "Robo ready", "Press button");
			if (startButton.buttonPressed()) {
				screen->resetLastSelectedOption();
				state = RoboStates::STATE_CHOOSEDIFFICULTY;
			}
			break;
		}
		case RoboStates::STATE_CLEANUP:
		{
			screen->updateMenu(RoboStates::STATE_CLEANUP, "clean up board", "Press button");
			if (startButton.buttonPressed()) {
				sendSerialMessage(MessageType::CleanUpDone);
				state = RoboStates::STATE_WAITING_BROKER;
				screen->updateMenu(RoboStates::STATE_WAITING_BROKER, "Waiting");
			}
			break;
		}
		case RoboStates::STATE_CHOOSEDIFFICULTY:
		{
			screen->updateMenu(RoboStates::STATE_CHOOSEDIFFICULTY, "Difficulty:");
			screen->updateSelectableOptions(state, poti.getSelectedOption());
			poti.changeSelection();
			if (poti.buttonPressed()) {
				screen->resetLastSelectedOption();
				GameConfig.difficulty = poti.getSelectedOption();
				state = RoboStates::STATE_PLAYORDER;

			}
			break;
		}
		case RoboStates::STATE_PLAYORDER:
		{
			screen->updateMenu(RoboStates::STATE_PLAYORDER, "Choose Playorder");
			screen->updateSelectableOptions(state, poti.getSelectedOption());
			poti.changeSelection();
			if (poti.buttonPressed()) {
				GameConfig.playorder = poti.getSelectedOption();
				byte config[] = { GameConfig.playorder, GameConfig.difficulty };
				sendSerialMessage(MessageType::Configuration, config, 2);
				screen->updateMenu(STATE_WAITING_BROKER, "Waiting");
				state = RoboStates::STATE_WAITING_BROKER;

			}
			break;
		}
		case RoboStates::STATE_WAITING_BROKER:
		{	
			if (startButton.buttonPressed()) {
				state = RoboStates::STATE_STOPGAME;
			}
			if (Serial.available() >= 2) {
				char* message = getSerialData();

				if (getMessageType(message) == MessageType::CleanUp) {
					state = RoboStates::STATE_CLEANUP;
				}
				else if (getMessageType(message) == MessageType::AlignCamera) {
					state = RoboStates::STATE_ALIGN_CAMERA;
				}
		
				else {
					activeGame(message);
				}
				free(message);
			}
			break;
		}
		case RoboStates::STATE_DONE:
		{
			sendSerialMessage(MessageType::Done);
			screen->updateMenu(STATE_WAITING_BROKER, "Waiting");
			state = RoboStates::STATE_WAITING_BROKER;
			break;
		}
		case RoboStates::STATE_DISP_EMPTY:
		{
			if (startButton.buttonPressed()) {
				sendSerialMessage(MessageType::DispFull);
				screen->updateMenu(RoboStates::STATE_DISP_FULL, "Waiting");
				state = RoboStates::STATE_WAITING_BROKER;
			}
			break;
		}
		case RoboStates::STATE_ALIGN_CAMERA:
		{
			screen->updateMenu(RoboStates::STATE_ALIGN_CAMERA, "Please align", "camera ");
			if (startButton.buttonPressed()) {
				sendSerialMessage(MessageType::AlignCameraDone);
				screen->updateMenu(RoboStates::STATE_ALIGN_DONE, "Waiting");
				state = RoboStates::STATE_WAITING_BROKER;
			}
			break;
		}
		case RoboStates::STATE_STOPGAME:
		{
			screen->updateMenu(RoboStates::STATE_STOPGAME, "Game was stopped!");
			sendSerialMessage(MessageType::StopGame);
			state = RoboStates::STATE_ENDGAME;
			delay(2000);
			break;
		}
		case RoboStates::STATE_ENDGAME:
		{
			screen->updateMenu(RoboStates::STATE_FINISHED, "Game over", "Press button");
			if (startButton.buttonPressed()) {
				state = RoboStates::STATE_READY;
				initStepperPosition();
			}
			break;
		}
	}
}
