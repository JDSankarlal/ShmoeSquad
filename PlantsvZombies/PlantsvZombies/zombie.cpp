#include "Zombie.h"

Zombie::Zombie()
{
	getData("assets/zombie.txt");//gives it ASCII data
	previousMoveTime = 0;
	moveInterval = 500;//move every 0.5s
	moveVector = { -1, 0 };//vector sprite will move in
	health = 100;
}


Zombie::~Zombie()
{
}

//deletes zombie if it hits the lefthand edge
bool Zombie::endCollision()
{
	if (getPosition().X == 13)
	{
		bool DeleteObject(
			//stuff
		);
		//delete zombieObject[i]; //Delete zombie
		return true;
	}
	else return false;
}