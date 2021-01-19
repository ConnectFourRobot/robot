#ifndef MESSAGETYPE_H
#define MESSAGETYPE_H

typedef enum Difficulty {
	EASY = 0,
	MEDIUM = 1,
	HARD = 2
}Difficulty;

typedef enum PayloadType {
	HUMAN = 0,
	ROBOT = 1,
	RANDOM = 2,
	HUMAN_ROBOT_INTERACTION = 254
}PayloadType;

typedef enum Direction {
	FORWARD = HIGH,
	BACKWARD = LOW
}Direction;

typedef enum MessageType {
	Booting = 0,
	Ready = 1,
	CleanUp = 2,
	CleanUpDone = 3,
	Configuration = 4,
	MoveRequest = 5,
	DetectedMove = 6,
	Move = 7,
	Done = 8,
	Endgame = 9,
	StopGame = 10,
	DispEmpty = 11,
	DispFull = 12,
	AlignCamera = 13,
	AlignCameraDone = 14,

}MessageType;



#endif