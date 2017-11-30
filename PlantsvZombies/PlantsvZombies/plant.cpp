#include "Plant.h"
#include <ctime>

Plant::Plant()
{
}

Plant::~Plant()
{
}



bool Plant::checkShoot(int time)//the number this returns tells the game which type of bullet to spawn
{
	if (time - previousShootTime >= shootInterval) {//shoot at set interval
		previousShootTime = time;
		return true;
	}
	else {
		return false;
	}
}

void Plant::shootingAnimation(vector<vector<string>>* spriteData, int time) {
}

void Plant::hurtAnimation(vector<vector<string>>* spriteData) {
}

void Plant::takeDamage(int dmg, int time) {
	if (health - dmg < 0) {
		health = 0;
	}
	else {
		health -= dmg;
	}
	if (dmg > 0) {
		colour = 0x0002;//dullGreen_black, sunflower will be dullYellow_black if spawning sun
		damageTime = time;
	}
}

bool Plant::shootBullet(int time) {
	if (shootTime > 0 && time - shootTime >= shootDelay) {
		shootTime = -1;
		return true;
	}
	else {
		return false;
	}
}


