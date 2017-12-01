#include "Wallnut.h"



Wallnut::Wallnut()
{
}

Wallnut::Wallnut(vector<vector<string>>* spriteData, int time)
{
	cost = 50;
	cooldown = 20000;
	type = WALLNUT;
	state = ALIVE;
	defaultColour = 0x000a;//green_black;
	defaultData = spriteData;
	resetData();
	previousFrameTime = time;

	health = 50;//x10 more than peashooters
}


Wallnut::~Wallnut()
{
}

void Wallnut::defaultAnimation() {
	colour = defaultColour;
	frameSequence = new int[4]{ 0, 1, 0, 2 };
	totalNumFrames = 4;
	frameTime = 1000;
}

void Wallnut::hurtAnimation(vector<vector<string>>* spriteData) {
	if (state != HURT) {
		state = HURT;
		setData(spriteData);//gives it new ASCII data for animation
		defaultData = spriteData;//change default sprite data so it goes back to it after a special animation
		frameTime = 500;
		frameSequence = new int[9]{ 0, 0, 0, 1, 1, 2, 1, 1, 2 };
		totalNumFrames = 9;
		frameNum = 0;
	}
}
