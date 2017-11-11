#include "zombie.h"

int getClock();

zombie::zombie()
{
}

zombie::~zombie()
{
}

//Random number between 1-5, will be responsible for putting the zombie in that row
int zombie::spawnRow()
{
	int spawnTime = rand() % 5 + 1;

	return spawnTime;
}

// Sets the spawning time of the zombies to every 20 seconds for now
int zombie::spawnTime()
{
	float currentTime = getClock();
	float lastSpawnTime = currentTime;
	if (currentTime >= (lastSpawnTime + 20))
	{
		spawnRow();
	}

}

//Responsible for the movespeed of the zombies
//The speed is just a placeholder number for now we will fix this for frames and such later.
int zombie::movement()
{
	int zombieMoveSpeed = 5;
}