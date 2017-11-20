#include "Plant.h"
#include <ctime>

Plant::Plant()
{
	getData("assets/peashooter.txt");//gives it ASCII data, default plant is peashooter
	previousShootTime = 0;
	shootInterval = 3000;//shoots every 3s
}

Plant::~Plant()
{
}

int Plant::plantHealth()
{
	int health = 100;
	return health;
}

bool Plant::shoot(int time)//the number this returns tells the game which type of bullet to spawn
{
	if (time - previousShootTime >= shootInterval) {//shoot at set interval
		previousShootTime = time;
		return true;
	}
	else {
		return false;
	}
}
