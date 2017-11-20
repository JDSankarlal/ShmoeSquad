#pragma once
#include "Sprite.h"
class Sun : public Sprite
{
public:
	Sun();
	Sun(int time);
	~Sun();

	bool updateLife(int time);

	int lifeTime;
};

