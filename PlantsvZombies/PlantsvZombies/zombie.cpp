#include "Zombie.h"

Zombie::Zombie()
{
	getData("assets/zombie.txt");//gives it ASCII data
	previousMoveTime = 0;
	moveInterval = 100;//move every 0.5s
	moveVector = { -1, 0 };//vector sprite will move in
	health = 100;
	row;
}


Zombie::~Zombie()
{
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