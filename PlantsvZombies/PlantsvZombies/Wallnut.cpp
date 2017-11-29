#include "Wallnut.h"



Wallnut::Wallnut()
{
}

Wallnut::Wallnut(vector<vector<string>>* spriteData, int time)
{
	type = WALLNUT;
	defaultColour = 0x000a;//green_black;
	defaultData = spriteData;
	resetData();
	previousFrameTime = time;

	health = 800;
}


Wallnut::~Wallnut()
{
}

void Wallnut::defaultAnimation() {
	colour = defaultColour;
	frameSequence = new int[4]{ 0,1,0,2 };
	totalNumFrames = 4;
	frameTime = 1000;
}

void Wallnut::hurtAnimation(vector<vector<string>>* spriteData) {
	setData(spriteData);//gives it new ASCII data for animation
	defaultData = spriteData;//change default sprite data so it goes back to it after a special animation
	frameSequence = new int[4]{ 0,1,0,2 };
	totalNumFrames = 4;
}