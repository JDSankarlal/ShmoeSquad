#include "Bullet.h"



Bullet::Bullet()//don't use this one
{
}

Bullet::Bullet(vector<vector<string>>* spriteData, int time)//use this constructor instead
{
	state = ALIVE;

	defaultColour = 0x000a;//green_black;
	defaultData = spriteData;
	resetData();
	previousFrameTime = time;

	previousMoveTime = 0;
	moveInterval = 75;
	moveVector = { 1, 0 };//vector sprite will move in


	//row = position();
	if (getPosition().Y == 12)
	{
		row = 1;
	}
	else if (getPosition().Y == 18)
	{
		row = 2;
	}
	else if (getPosition().Y == 24)
	{
		row = 3;
	}
	else if (getPosition().Y == 30)
	{
		row = 4;
	}
	else if (getPosition().Y == 36)
	{
		row = 5;
	}
}

Bullet::~Bullet()
{
}

void Bullet::hit() {
	isAlive = false;
}

void Bullet::defaultAnimation() {
	colour = defaultColour;
	frameSequence = new int[4]{ 0,1,2,3 };
	totalNumFrames = 4;
	frameTime = 375;
}

//Deletes the bullet if it hits the righthand edge
bool Bullet::hitEdge()
{
	if (getPosition().X >= 135)
	{
		//VECTOR::EREASE <- LOWERCASE 
		//Delete Bullet
		return true;
	}
	else return false;
}

/*bool Bullet::hitZombie()
{
	if (getPosition().Y == zombies[i] - 2)
	{
		return true;
	}
	else return false;
}*/
int Bullet::position()
{
	if (getPosition().Y == 12)
	{
		row = 1;
	}
	else if (getPosition().Y == 18)
	{
		row = 2;
	}
	else if (getPosition().Y == 24)
	{
		row = 3;
	}
	else if (getPosition().Y == 30)
	{
		row = 4;
	}
	else if (getPosition().Y == 36)
	{
		row = 5;
	}
	return row;
}
