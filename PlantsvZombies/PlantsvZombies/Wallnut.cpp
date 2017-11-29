#include "Wallnut.h"



Wallnut::Wallnut()
{
}

Wallnut::Wallnut(vector<vector<string>>* spriteData, int time)
{
	type = WALLNUT;
	setData(spriteData);//gives it ASCII data
	frameSequence = new int[4]{ 0,1,0,2 };
	totalNumFrames = 4;
	frameTime = 1000;//change animation frame every 0.522s, synced with the bpm of the music!
	previousFrameTime = time;

	health = 400;
}


Wallnut::~Wallnut()
{
}
