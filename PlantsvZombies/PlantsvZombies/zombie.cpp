#include "zombie.h"


int getClock();

zombie::zombie()
{
}


zombie::~zombie()
{
}

int zombie::spawnRow()
{
	int spawnTime = rand() % 5 + 1;

	return spawnTime;
}

int zombie::spawnTime()
{
	float currentTime = getClock();
	float lastSpawnTime = currentTime;
	if (currentTime > lastSpawnTime)
	{
		//if __ seconds greater the spawn on spawnRow()
	}

}