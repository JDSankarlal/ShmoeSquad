#include "Bullet.h"



Bullet::Bullet()//don't use this one
{
}

Bullet::Bullet(vector<vector<string>> spriteData, int time)//use this constructor instead
{
	setData(spriteData);//gives it ASCII data
	
	frameSequence = new int[4]{ 0,1,2,3 };
	totalNumFrames = 4;
	frameTime = 350;

	previousMoveTime = 0;
	moveInterval = 100;//move every 0.1s
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

//Deletes the bullet if it hits the righthand edge
bool Bullet::hitEdge()
{
	if (getPosition().X == 121)//instead of hard coding a number, use the bullet's (position.x + size.x) and see if it's greater than the grid's (position.x + size.x)
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