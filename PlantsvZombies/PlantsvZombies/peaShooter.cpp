#include "Peashooter.h"



Peashooter::Peashooter()
{
	type = PEASHOOTER;
	getData("assets/peashooter.txt");//gives it ASCII data
	previousShootTime = 0;
	shootInterval = 3000;//shoots every 3s
	health = 100;
}

Peashooter::Peashooter(int time)
{
	type = PEASHOOTER;
	getData("assets/peashooter.txt");//gives it ASCII data
	previousShootTime = time;
	shootInterval = 3000;//shoots every 3s
	frameSequence = new int[4]{ 0,1,2,1 };
	totalNumFrames = 4;
	frameTime = 522;//change animation frame every 0.522s, synced witht he bpm of the music!
}


Peashooter::~Peashooter()
{
}
