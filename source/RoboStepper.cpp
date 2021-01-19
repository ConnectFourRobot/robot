#include "RoboStepper.h"


void RoboStepper::goToHomePosition() {								//move to press the stepper button (initial position)		
	this->_axisStepper->setMaxSpeed(this->_maxSpeed);
	this->_axisStepper->setAcceleration(this->_accelaration);
	this->_axisStepper->moveTo(-6000);								//TODO: change dummy value
}

void RoboStepper::configureMove(int column)               // move to the selected column
{                            // just configure move settings if not already done
	int distance;

	distance = this->_distanceToFirstColumn + this->_distanceBetweenColumns * column;
	this->_axisStepper->moveTo(distance);
	this->_axisStepper->setMaxSpeed(this->_maxSpeed);
	this->_axisStepper->setAcceleration(this->_accelaration);
}

void RoboStepper::stopMotor()								   // stop stepper motor when someone reaches into the robot
{
	this->_runAllowed = false;
	this->_axisStepper->stop();
	this->_axisStepper->disableOutputs();
}




void RoboStepper::continuousRun()								// called at beginning of loop(). Does one step per loop		
{
	this->_axisStepper->enableOutputs();
	this->_axisStepper->run();
}

long RoboStepper::getPosition()											//get current stepper position, not used yet
{
	return this->_axisStepper->currentPosition();
}

/*
void RoboStepper::clearInterrupt()        //not used yet
{
	this->_runAllowed = true;
}
*/
bool RoboStepper::positionReached()
{
	return this->_axisStepper->distanceToGo() == 0;
}
void RoboStepper::setHomePositionReached()
{
	this->_axisStepper->setCurrentPosition(0);
}

void RoboStepper::setRunAllowed(bool value) {
	this->_runAllowed = value;
}

bool RoboStepper::checkRunAllowed()
{
	return this->_runAllowed;
}

long RoboStepper::distanceToGo() {
	return this->_axisStepper->distanceToGo();
}
