#pragma once
#include "Sprite.h"

class Plant : public Sprite
{
public:
	Plant();
	~Plant();
	int plantHealth();
	bool shoot(int time);
};

