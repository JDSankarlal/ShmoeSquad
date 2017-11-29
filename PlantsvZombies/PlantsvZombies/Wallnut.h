#pragma once
#include "Plant.h"
class Wallnut : public Plant
{
public:
	Wallnut();
	Wallnut(vector<vector<string>>* spriteData, int time);
	~Wallnut();

	void defaultAnimation();
	void hurtAnimation(vector<vector<string>>* spriteData);//set Wallnut's sprite and animation data when it's below 1/4 health
};

