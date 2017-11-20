#include "Sunflower.h"



Sunflower::Sunflower()
{
	type = SUNFLOWER;
	getData("assets/sunflower.txt");//gives it ASCII data
	previousShootTime = 0;
	shootInterval = 10000;//shoots every 10s
}


Sunflower::~Sunflower()
{
}
