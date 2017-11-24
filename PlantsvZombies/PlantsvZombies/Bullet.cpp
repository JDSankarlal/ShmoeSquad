#include "Bullet.h"



Bullet::Bullet()
{
	getData("assets/bullet.txt");//gives it ASCII data
	previousMoveTime = 0;
	moveInterval = 100;//move every 0.1s
	moveVector = { 1, 0 };//vector sprite will move in
}


Bullet::~Bullet()
{
}

//Deletes the bullet if it hits the righthand edge
bool Bullet::hitEdge()
{
	if (getPosition().X == 121)
	{
		//VECTOR::EREASE <- LOWERCASE 
		//Delete Bullet
		return true;
	}
	else return false;
}