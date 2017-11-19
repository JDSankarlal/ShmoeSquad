#include "Sun.h"



Sun::Sun()
{
	getData("assets/sun.txt");//gives it ASCII data
	lifeTime = 10;
}


Sun::~Sun()
{
}

bool Sun::updateLife() {
	lifeTime--;
	if (lifeTime <= 0) {
		return false;
	}
	else {
		return true;
	}
}