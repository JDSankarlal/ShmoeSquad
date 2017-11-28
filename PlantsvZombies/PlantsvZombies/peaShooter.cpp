#include "Peashooter.h"



Peashooter::Peashooter()
{
}

Peashooter::Peashooter(vector<vector<string>>* spriteData, int time)
{
	type = PEASHOOTER;
	setData(spriteData);//gives it ASCII data
	frameSequence = new int[4]{ 0,1,0,2 };
	totalNumFrames = 4;
	frameTime = 522;//change animation frame every 0.522s, synced with the bpm of the music!

	previousShootTime = time;
	shootInterval = 3000;//shoots every 3s
}


Peashooter::~Peashooter()
{
}
