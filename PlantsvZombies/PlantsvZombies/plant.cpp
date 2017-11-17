#include "Plant.h"
#include <ctime>

Plant::Plant()
{

}

Plant::~Plant()
{
}

int Plant::plantHealth()
{
	int health = 100;
	return health;
}

bool Plant::shoot(int time)
{
	if (time % 10 == 0) {
		return true;
	}
	else {
		return false;
	}

	/*clock_t SHOTS_FIRED;
	SHOTS_FIRED = clock();

	//cout << GAME_TIME << endl;
	if (((clock() - SHOTS_FIRED) / CLOCKS_PER_SEC) >= 1.5f)  //Spawns a sun from SKY every 10 seconds. Will have to figure out how to spawn it every 10 local seconds relative to individual sunflowers spawn time
	{
		printf("O");
		SHOTS_FIRED = clock();
	}*/
}