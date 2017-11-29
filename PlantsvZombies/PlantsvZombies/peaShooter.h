#pragma once
#include "Plant.h"
class Peashooter : public Plant
{
public:
	Peashooter();
	Peashooter(vector<vector<string>>* spriteData, int time);
	~Peashooter();

	void shootingAnimation(vector<vector<string>>* spriteData, int time);
	void defaultAnimation();

};
