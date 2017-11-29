#include "Sunflower.h"



Sunflower::Sunflower()
{
}

Sunflower::Sunflower(vector<vector<string>>* spriteData, int time)
{
	type = SUNFLOWER;
	defaultData = spriteData;
	resetData();
	previousFrameTime = time;

	previousShootTime = time;
	shootInterval = 8000;//shines every 8s
}

Sunflower::~Sunflower()
{
}

void Sunflower::defaultAnimation() {
	colour = 0x000a;//green_black
	frameSequence = new int[4]{ 0,1,0,2 };
	totalNumFrames = 4;
	frameTime = 500;//change animation frame every 0.522s, synced with the bpm of the music!
}

void Sunflower::shootingAnimation(vector<vector<string>>* spriteData, int time) {
	colour = 0x000e;//yellow_black
	inAnimation = true;
	numLoops = 4;

	setData(spriteData);//gives it new ASCII data for animation
	frameSequence = new int[4]{ 0,1,2,1 };
	totalNumFrames = 4;
	frameTime = 150;//change animation frame every 0.5s
	previousFrameTime = time;
	frameNum = 0;
}
