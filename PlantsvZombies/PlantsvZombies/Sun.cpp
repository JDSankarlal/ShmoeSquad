#include "Sun.h"



Sun::Sun()
{
}

Sun::Sun(vector<vector<string>>* spriteData, int time)
{
	colour = 0x000e;//yellow_black
	defaultColour = colour;
	defaultData = spriteData;
	setData(spriteData);//gives it ASCII data
	frameSequence = new int[1]{ 0 };
	totalNumFrames = 1;
	//frameTime = 200;//change animation frame every 0.5s
	previousFrameTime = time;

	lifeTime = time + 3000;//suns stays alive for 2 seconds
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
