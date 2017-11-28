#include "Sunflower.h"



Sunflower::Sunflower()
{
}

Sunflower::Sunflower(vector<vector<string>>* spriteData, int time)
{
	type = SUNFLOWER;
	setData(spriteData);//gives it ASCII data
	frameSequence = new int[4]{ 0,1,0,2 };
	totalNumFrames = 4;
	frameTime = 522;//change animation frame every 0.522s, synced with the bpm of the music!
	previousFrameTime = time;

	previousShootTime = time;
	shootInterval = 6000;//shoots every 6s
}

Sunflower::~Sunflower()
{
}
