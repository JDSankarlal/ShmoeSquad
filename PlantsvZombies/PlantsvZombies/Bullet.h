#pragma once
#include "Sprite.h"
class Bullet : public Sprite
{
public:
	Bullet();
	~Bullet();
	bool hitEdge();
	bool hitZombie();
	int position();
	int row;
};

