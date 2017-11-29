#include "Peashooter.h"



Peashooter::Peashooter()
{
}

Peashooter::Peashooter(vector<vector<string>>* spriteData, int time)
{
	type = PEASHOOTER;
	defaultData = spriteData;
	setData(spriteData);//gives it ASCII data
	frameSequence = new int[4]{ 0,1,0,2 };
	totalNumFrames = 4;
	frameTime = 522;//change animation frame every 0.522s, synced with the bpm of the music!
	previousFrameTime = time;

	shootDelay = 1000;

	previousShootTime = time;
	shootInterval = 5000;//shoots every 5s
}


Peashooter::~Peashooter()
{
}

void Peashooter::shootingAnimation(vector<vector<string>>* spriteData, int time) {
	shootTime = time;
	inAnimation = true;

	setData(spriteData);//gives it new ASCII data for animation
	frameSequence = new int[3]{ 0, 1, 2 };
	totalNumFrames = 3;
	frameTime = 500;//change animation frame every 0.522s, synced with the bpm of the music!
	previousFrameTime = time;
	frameNum = 0;
}

void Peashooter::defaultAnimation() {
	frameSequence = new int[4]{ 0,1,0,2 };
	totalNumFrames = 4;
	frameTime = 500;//change animation frame every 0.522s, synced with the bpm of the music!
}
