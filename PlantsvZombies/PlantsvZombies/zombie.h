#pragma once
#include <ctime>
#include <stdlib.h>

class zombie
{
public:
	zombie();
	~zombie();

	int spawnRow();
	int spawnTime();
	int movement();
};