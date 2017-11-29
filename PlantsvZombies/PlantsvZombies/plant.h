#pragma once
#include "Sprite.h"

class Plant : public Sprite
{
public:
	Plant();
	~Plant();
	enum plantType {
		SUNFLOWER,
		PEASHOOTER,
		WALLNUT
	};
	plantType getType() {
		return type;
	}

	int shootInterval;//time in ms between shots
	int previousShootTime;//stores last time the plant shot
	int health;

	virtual bool shoot(int time);//function used to check whether plant should shoot on the current frame

	virtual void shootingAnimation(vector<vector<string>>* spriteData, int time);

protected://like private but can be accessed by child classes
	plantType type;//don't want to modify this ever
};

