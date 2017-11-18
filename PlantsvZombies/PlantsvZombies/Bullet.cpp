#include "Bullet.h"



Bullet::Bullet()
{
	getData("assets/bullet.txt");//gives it ASCII data
	movePosition = { 1, 0 };
}


Bullet::~Bullet()
{
}
