#pragma once
#include "Sprite.h"

class Zombie : public Sprite
{
public:
	Zombie();
	Zombie(vector<vector<string>>* spriteData, int time);
	~Zombie();

	void defaultAnimation();
	void takeDamage(int time);//change colour of sprite so it flashes when taking damage

	int health;
	int row;
	bool endCollision();
	bool shot();
	int position();
};