#include "Sun.h"



Sun::Sun()
{
	getData("assets/sun.txt");//gives it ASCII data
	lifeTime = 2000;//suns stays alive for 2 seconds
}

Sun::Sun(int time)
{
	getData("assets/sun.txt");//gives it ASCII data
	lifeTime = time + 2000;//suns stays alive for 2 seconds
}


Sun::~Sun()
{
}

bool Sun::updateLife(int time) {
	if (lifeTime - time <= 0) {
		return false;//sun is dead
	}
	else {
		return true;//sun is still alive
	}
}