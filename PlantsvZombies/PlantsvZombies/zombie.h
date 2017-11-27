#pragma once
#include "Sprite.h"

class Zombie : public Sprite
{
public:
	Zombie();
	~Zombie();
	int health;
	int row;
	bool endCollision();
	bool shot();
	int position();
};