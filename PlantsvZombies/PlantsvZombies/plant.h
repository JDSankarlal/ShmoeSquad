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

	int shootTime = -1;//used for delaying spawning the bullet to sync with shooting animation
	int shootDelay = 0;//the delay between when the plant is updated to shoot and when the bullet actually spawns

	int shootInterval;//time in ms between shots
	int previousShootTime;//stores last time the plant shot
	int health;

	virtual bool checkShoot(int time);//function used to check whether plant should shoot on the current frame

	virtual void shootingAnimation(vector<vector<string>>* spriteData, int time);//starts plant's shooting animation
	void takeDamage(int time);//change colour of sprite so it flashes when taking damage
	virtual bool shootBullet(int time);//spawn a bullet when plants shooting animation finishes

protected://like private but can be accessed by child classes
	plantType type;//don't want to modify this ever
};
