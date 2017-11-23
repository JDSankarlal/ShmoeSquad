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
	shootInterval = 5000;//shoots every 10s
}

Sunflower::~Sunflower()
{
}
