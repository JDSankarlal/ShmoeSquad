#pragma once
#include "Plant.h"
class Sunflower : public Plant
{
public:
	Sunflower();
	Sunflower(vector<vector<string>>* spriteData, int time);
	~Sunflower();

	void defaultAnimation();
	void shootingAnimation(vector<vector<string>>* spriteData, int time);
};
