#pragma once
#include "Sprite.h"

class Plant : public Sprite
{
public:
	Plant();
	~Plant();
	int plantHealth();
	virtual bool shoot(int time);//function used to check whether plant should shoot on the current frame

	enum plantType {
		SUNFLOWER,
		PEASHOOTER,
		WALLNUT
	};
	plantType getType() {
		return type;
	}

protected://like private but can be accessed by child classes
	plantType type;
};

