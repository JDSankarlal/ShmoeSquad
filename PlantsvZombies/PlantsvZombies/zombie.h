#pragma once
#include "Sprite.h"

class Zombie : public Sprite
{
public:
	Zombie();
	Zombie(vector<vector<string>>* spriteData, int time);
	~Zombie();
	int health;
	int row;
	bool endCollision();
	bool shot();
	int position();
};