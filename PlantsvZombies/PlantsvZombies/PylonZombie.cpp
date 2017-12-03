#include "PylonZombie.h"



PylonZombie::PylonZombie()
{
}

PylonZombie::PylonZombie(vector<vector<string>>* spriteData, int time)
{
	type = PYLON;
	health = 42;
	halfHP = (health / 2) + 2;
	state = ALIVE;
	isEating = false;
	previousMoveTime = time;
	moveInterval = 490;//move every 1.0s
	moveVector = { -1, 0 };//vector sprite will move in

	defaultColour = 0x000b;//turqoise_black
	defaultData = spriteData;
	resetData();
	previousFrameTime = time;
}


PylonZombie::~PylonZombie()
{
}
