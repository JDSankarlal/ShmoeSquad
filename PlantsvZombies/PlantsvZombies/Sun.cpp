#include "Sun.h"



Sun::Sun()
{
}

Sun::Sun(vector<vector<string>>* spriteData, int time)
{
	setData(spriteData);//gives it ASCII data
	lifeTime = time + 3000;//suns stays alive for 2 seconds
	frameSequence = new int[4]{ 0,1,2,1 };
	totalNumFrames = 4;
	frameTime = 200;//change animation frame every 0.5s
	previousFrameTime = time;
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