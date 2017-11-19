#pragma once
#include "Sprite.h"
class Sun : public Sprite
{
public:
	Sun();
	~Sun();

	bool updateLife();

	int lifeTime;
};

