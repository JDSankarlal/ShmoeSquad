#include "Wallnut.h"



Wallnut::Wallnut()
{
}

Wallnut::Wallnut(vector<vector<string>>* spriteData, int time)
{
	type = WALLNUT;
	defaultData = spriteData;
	resetData();
	previousFrameTime = time;

	health = 400;
}


Wallnut::~Wallnut()
{
}

void Wallnut::defaultAnimation() {
	colour = 0x000a;//green_black
	frameSequence = new int[4]{ 0,1,0,2 };
	totalNumFrames = 4;
	frameTime = 1000;
}