#include "sun.h"
#include <ctime>
#include <cstdio>

int getClock();

sun::sun()
{
}


sun::~sun()
{
}

//Calculates the amount of sun that falls from the sky, sun falls every 10 seconds as said on the wiki
int sun::sunFall()
{
	int sun = 0;
	float timeSinceLastSunFall;

	float currentTime = getClock();
	float lastFallTime = currentTime;
	if (currentTime >= (lastFallTime + 10))
	{
		sun += 25;
	}
	return sun;

}
