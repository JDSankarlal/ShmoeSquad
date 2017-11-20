#include "Bullet.h"



Bullet::Bullet()
{
	getData("assets/bullet.txt");//gives it ASCII data
	previousMoveTime = 0;
	moveInterval = 200;//move every 0.2s
	moveVector = { 1, 0 };//vector sprite will move in
}


Bullet::~Bullet()
{
}
