#pragma once
#include "zombie.h"
class PylonZombie :
	public Zombie
{
public:
	PylonZombie();
	PylonZombie(vector<vector<string>>* spriteData, int time);
	~PylonZombie();
};

