#include "Zombie.h"

Zombie::Zombie()
{
}

Zombie::Zombie(vector<vector<string>>* spriteData, int time)
{
	state = ALIVE;

	previousMoveTime = time;
	moveInterval = 1000;//move every 1.0s
	moveVector = { -1, 0 };//vector sprite will move in

	defaultColour = 0x000b;//turqoise_black
	defaultData = spriteData;
	resetData();
	previousFrameTime = time;

	health = 100;
	row;
}

Zombie::~Zombie()
{
}

void Zombie::setState(State givenState) {
	state = givenState;
}

Zombie::State Zombie::getState() {
	return state;
}

void Zombie::defaultAnimation() {
	colour = defaultColour;
	frameSequence = new int[4]{ 0, 1, 0, 2 };
	totalNumFrames = 4;
	frameTime = moveInterval / 2;//change animation frame every 0.4s
}

void Zombie::hurtAnimation(vector<vector<string>>* spriteData) {
	state = HURT;

	setData(spriteData);//gives it new ASCII data for animation
	defaultData = spriteData;//change default sprite data so it goes back to it after a special animation
	frameSequence = new int[4]{ 0, 1, 0, 2 };
	totalNumFrames = 4;
}

void Zombie::eatingAnimation(vector<vector<string>>* spriteData, vector<vector<string>>* spriteData2, int time) {
	if (state == ALIVE) {
		setData(spriteData);//set to normal eating
	}
	else if (state == HURT) {
		setData(spriteData2);//set to hurt eating animation
	}
	frameSequence = new int[3]{ 0, 1, 2 };//both have the same frame sequence
	totalNumFrames = 3;
	frameTime = 250;//change animation frame every 0.522s, synced with the bpm of the music!
	previousFrameTime = time;
	frameNum = 0;
}

void Zombie::deathAnimation(vector<vector<string>>* spriteData, int time) {
	state = DEAD;
	if (inAnimation == false) {
		deathTime = time;
		inAnimation = true;

		setData(spriteData);//gives it new ASCII data for animation
		frameSequence = new int[6]{ 0, 1, 2, 3, 4, 5 };//change this
		totalNumFrames = 6;//change this
		frameTime = 250;//change this
		previousFrameTime = time;
		frameNum = 0;
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


void Zombie::takeDamage(int time) {
	colour = colour - 0x0008;//dullTurqoise_black
	damageTime = time;
}

//deletes zombie if it hits the lefthand edge
bool Zombie::endCollision()
{
	if (getPosition().X == 13)
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
