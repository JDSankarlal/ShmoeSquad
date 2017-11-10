#pragma once
#include "Object.h"
#include <ctime>
#include <stdlib.h>

class zombie : public Object
{
public:
	zombie();
	~zombie();

	int spawnRow();
	int spawnTime();
};