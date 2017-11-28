#include "Sunflower.h"



Sunflower::Sunflower()
{
	type = SUNFLOWER;
	getData("assets/sunflower.txt");//gives it ASCII data
	previousShootTime = 0;
	shootInterval = 5000;//shoots every 10s
	health = 100;
}

Sunflower::Sunflower(int time)
{
	type = SUNFLOWER;
	getData("assets/sunflower.txt");//gives it ASCII data
	previousShootTime = time;
	shootInterval = 6000;//shoots every 6s
	frameSequence = new int[4]{ 0,1,2,1 };
	totalNumFrames = 4;
	frameTime = 522;//change animation frame every 0.522s, synced witht he bpm of the music!
}

Sunflower::~Sunflower()
{
}
