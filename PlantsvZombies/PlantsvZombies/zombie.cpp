#include "Zombie.h"

Zombie::Zombie()
{
	getData("assets/zombie.txt");//gives it ASCII data
	movePosition = { -1, 0 };
}


Zombie::~Zombie()
{
}

