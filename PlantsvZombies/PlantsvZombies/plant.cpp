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

void Plant::takeDamage(int time) {
	colour = 0x0002;//dullGreen_black
	damageTime = time;
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
