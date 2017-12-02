#include "Peashooter.h"



Peashooter::Peashooter()
{
}

Peashooter::Peashooter(vector<vector<string>>* spriteData, int time)
{
	health = 5;
	cost = 100;
	cooldown = 5000;
	type = PEASHOOTER;
	defaultColour = 0x000a;//green_black;
	defaultData = spriteData;
	resetData();
	previousFrameTime = time;

	shootDelay = 600;
	health = 4;
	shootInterval = 3000;//shoots every 3s
	previousShootTime = time - shootInterval;
}

Peashooter::~Peashooter()
{
}

void Peashooter::shootingAnimation(vector<vector<string>>* spriteData, int time) {
	if (inAnimation == false){
		shootTime = time;
		inAnimation = true;

		defaultFrameNum = frameNum + 1;
		if (defaultFrameNum >= totalNumFrames) { defaultFrameNum = 0; }

		setData(spriteData);//gives it new ASCII data for animation
		frameSequence = new int[7]{ 0, 0, 1, 1, 2 ,2, 2};
		totalNumFrames = 7;
		frameTime = 150;
		previousFrameTime = time;
		frameNum = 0;
	}
}

void Peashooter::defaultAnimation() {
	colour = defaultColour;
	frameSequence = new int[4]{ 0,1,0,2 };
	totalNumFrames = 4;
	frameTime = 500;//change animation frame every 0.522s, synced with the bpm of the music!
}
