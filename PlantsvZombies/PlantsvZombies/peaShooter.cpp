#include "Peashooter.h"



Peashooter::Peashooter()
{
	type = PEASHOOTER;
	getData("assets/peashooter.txt");//gives it ASCII data
	previousShootTime = 0;
	shootInterval = 3000;//shoots every 3s
}

Peashooter::Peashooter(int time)
{
	type = PEASHOOTER;
	getData("assets/peashooter.txt");//gives it ASCII data
	previousShootTime = time;
	shootInterval = 3000;//shoots every 3s
}


Peashooter::~Peashooter()
{
}
