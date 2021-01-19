#ifndef ROBOSTEPPER_H
#define ROBOSTEPPER_H
#include <AccelStepper.h>
#include "MessageType.h"

class RoboStepper{
private:
	bool _runAllowed = false;               //allow stepper to do run() - stop stepper if serial interrupt (= MessageType::Interrupt) occurs	
	bool _reachedHomePosition = false;		//is set true, when stepper reaches the HomeButton (-> pin interrupt). initial position at the beginning of the game 
	int _maxSpeed = 0;
	int _accelaration = 0;
	int _column = 0; // only debugging
	int _distanceToFirstColumn;
	int _distanceBetweenColumns;
	AccelStepper* _axisStepper;

public:
	RoboStepper() = delete;
	RoboStepper(int distanceToFirstColumn, int distanceBetweenColumns, int maxSpeed, int acceleration) : _distanceToFirstColumn(distanceToFirstColumn),
		_distanceBetweenColumns(distanceBetweenColumns), _maxSpeed(maxSpeed), _accelaration(acceleration) {
		_axisStepper = new AccelStepper(AccelStepper::FULL4WIRE, 10, 11, 12, 13);   // motor interfaceType + 4 pins

	};
	void goToHomePosition();
	void configureMove(int column);
	void stopMotor();
	void continuousRun();
	long getPosition();
	//void clearInterrupt();              //not used yet
	bool positionReached();
	void setHomePositionReached();
	void setRunAllowed(bool value);
	bool checkRunAllowed();
	long distanceToGo();
};


#endif // !STEPPER_H
