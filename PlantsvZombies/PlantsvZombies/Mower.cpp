#include "Mower.h"



Mower::Mower()
{
}

Mower::Mower(vector<vector<string>>* spriteData, int time)
{
	state = WAITING;

	defaultColour = 0x0004;//dullRed_black
	defaultData = spriteData;
	resetData();
	previousFrameTime = time;
}


Mower::~Mower()
{
}

void Mower::defaultAnimation() {
	colour = defaultColour;
	frameSequence = new int[1]{ 0 };
	totalNumFrames = 1;
}

void Mower::activate(int time) {
	if (state != ACTIVATED) {
		state = ACTIVATED;

		colour = 0x0004 + 0x0008;//red_black

		moveInterval = 50;//move every 0.1s
		moveVector = { 1, 0 };//vector sprite will move in
		previousMoveTime = time;

		frameSequence = new int[4]{ 0, 1, 2, 3 };
		totalNumFrames = 4;
		frameTime = moveInterval * 2;
		previousFrameTime = time;
	}
}

bool Mower::hitEdge()
{
	if (getPosition().X >= 135)
	{
		return true;
	}
	else {
		return false;
	}
}