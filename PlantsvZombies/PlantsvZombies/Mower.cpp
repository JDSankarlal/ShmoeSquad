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

		moveInterval = 250;//move every 0.25s
		moveVector = { 1, 0 };//vector sprite will move in
		previousMoveTime = time;

		frameSequence = new int[1]{ 0 };
		totalNumFrames = 1;
		frameTime = moveInterval;//change animation frame every 0.125s
		previousFrameTime = time;
	}
}
