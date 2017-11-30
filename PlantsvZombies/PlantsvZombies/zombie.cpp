#include "Zombie.h"

Zombie::Zombie()
{
}

Zombie::Zombie(vector<vector<string>>* spriteData, int time)
{
	state = ALIVE;

	previousMoveTime = time;
	moveInterval = 500;//move every 1.0s
	moveVector = { -1, 0 };//vector sprite will move in

	defaultColour = 0x000b;//turqoise_black
	defaultData = spriteData;
	resetData();
	previousFrameTime = time;

	health = 400;
	row;
}

Zombie::~Zombie()
{
}

Zombie::State Zombie::getState() {
	return state;
}

void Zombie::defaultAnimation() {
	moveInterval = 500;

	isEating = false;
	colour = defaultColour;
	frameSequence = new int[4]{ 0, 1, 0, 2 };
	totalNumFrames = 4;
	frameTime = moveInterval;

	//faster animation, looks kinda janky:
	//frameSequence = new int[8]{ 0, 0, 0, 1, 0, 0, 0, 2 };
	//totalNumFrames = 8;
	//frameTime = moveInterval / 4;
}

void Zombie::hurtAnimation(vector<vector<string>>* spriteData) {
	if (state != HURT && state != DEAD) {
		state = HURT;
		if (isEating == false) {
			setData(spriteData);//gives it new ASCII data for animation
			defaultData = spriteData;//change default sprite data so it goes back to it after a special animation
		}
		else {
			isEating = false;
		}
	}
}

void Zombie::eatingAnimation(vector<vector<string>>* spriteData, vector<vector<string>>* spriteData2, int time) {
	if (isEating == false && state != DEAD) {
		isEating = true;
		moveInterval = -1;//don't move
		if (state == ALIVE) {
			setData(spriteData);//set to normal eating
		}
		else if (state == HURT) {
			setData(spriteData2);//set to hurt eating animation
		}
		frameSequence = new int[3]{ 0, 1, 2 };//both have the same frame sequence
		totalNumFrames = 3;
		frameTime = 250;
		previousFrameTime = time;
		frameNum = 0;
	}
}

void Zombie::deathAnimation(vector<vector<string>>* spriteData, int time) {
	if (state != DEAD) {
		state = DEAD;
		moveInterval = -1;//don't move
		deathTime = time;

		setData(spriteData);//gives it new ASCII data for animation
		frameSequence = new int[7]{ 0, 1, 2, 3, 4, 5, 4 };//change this
		totalNumFrames = 7;//change this
		frameTime = 350;//change this
		previousFrameTime = time;
		frameNum = 0;

		deathDelay = totalNumFrames * frameTime;
	}
}

bool Zombie::killZombie(int time) {
	if (state == DEAD) {
		if (time - deathTime >= deathDelay) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}


void Zombie::takeDamage(int dmg, int time) {
	if (health - dmg < 0) {
		health = 0;
	}
	else {
		health -= dmg;
	}
	colour = 0x000b - 0x0008;//dullTurqoise_black
	damageTime = time;
}

int Zombie::dealDamage(int time) {
	dmgTime = time;
	return dmg;
}

//deletes zombie if it hits the lefthand edge
bool Zombie::endCollision()
{
	if (getPosition().X <= 12)
	{
		
		return true;
	}
	else return false;
}

bool Zombie::shot()
{
	health -= 50;
	return true;
}

int Zombie::position()
{
	if (getPosition().Y == 11)
	{
		row = 1;
	}
	else if (getPosition().Y == 17)
	{
		row = 1;
	}
	else if (getPosition().Y == 23)
	{
		row = 1;
	}
	else if (getPosition().Y == 29)
	{
		row = 1;
	}
	else if (getPosition().Y == 35)
	{
		row = 1;
	}
	return row;
}
