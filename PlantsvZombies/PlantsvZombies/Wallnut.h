#pragma once
#include "Plant.h"
class Wallnut : public Plant
{
public:
	Wallnut();
	Wallnut(vector<vector<string>>* spriteData, int time);
	~Wallnut();

	void defaultAnimation();
};

