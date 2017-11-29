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

	previousShootTime = time;
	shootInterval = 3000;//shoots every 3s
}


Peashooter::~Peashooter()
{
}

void Peashooter::shootingAnimation(vector<vector<string>>* spriteData, int time) {
	inAnimation = true;

	setData(spriteData);//gives it new ASCII data for animation
	frameSequence = new int[4]{ 0,1,0,2 };
	totalNumFrames = 4;
	frameTime = 522;//change animation frame every 0.522s, synced with the bpm of the music!
	previousFrameTime = time;
	frameNum = 0;
}

void Peashooter::defaultAnimation() {
	frameSequence = new int[4]{ 0,1,0,2 };
	totalNumFrames = 4;
	frameTime = 522;//change animation frame every 0.522s, synced with the bpm of the music!
}
