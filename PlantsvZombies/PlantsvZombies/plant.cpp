#include "Plant.h"
#include <ctime>

Plant::Plant()
{
}

Plant::~Plant()
{
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
