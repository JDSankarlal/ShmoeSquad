#include "Plant.h"
#include <ctime>

Plant::Plant()
{
	getData("assets/peashooter.txt");//gives it ASCII data, default plant is peashooter
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
	if (time % 10 == 0) {//shoot every 10 frames
		return true;
	}
	else {
		return false;
	}

}
