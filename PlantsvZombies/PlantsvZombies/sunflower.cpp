#include "Sunflower.h"



Sunflower::Sunflower()
{
}

Sunflower::Sunflower(vector<vector<string>>* spriteData, int time)
{
	type = SUNFLOWER;
	defaultColour = 0x000a;//green_black;
	defaultData = spriteData;
	resetData();
	previousFrameTime = time;

	shootInterval = 24000;//shines every 24s
	previousShootTime = time - shootInterval + 7000;//will shine once 7 seconds after being planted
	
}

Sunflower::~Sunflower()
{
}

void Sunflower::defaultAnimation() {
	colour = defaultColour;
	frameSequence = new int[4]{ 0,1,0,2 };
	totalNumFrames = 4;
	frameTime = 500;//change animation frame every 0.522s, synced with the bpm of the music!
}

void Sunflower::shootingAnimation(vector<vector<string>>* spriteData, int time) {
	if (inAnimation == false) {
		colour = 0x000e;//yellow_black
		inAnimation = true;
		numLoops = 4;

		defaultFrameNum = frameNum + 1;
		if (defaultFrameNum >= totalNumFrames) { defaultFrameNum = 0; }

		setData(spriteData);//gives it new ASCII data for animation
		frameSequence = new int[4]{ 0,1,2,1 };
		totalNumFrames = 4;
		frameTime = 150;//change animation frame every 0.5s
		previousFrameTime = time;
		frameNum = 0;
	}
}
