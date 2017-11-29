#pragma once
#include "Sprite.h"
class Bullet : public Sprite
{
public:
	Bullet();
	Bullet(vector<vector<string>>* spriteData, int time);
	~Bullet();

	void defaultAnimation();

	bool hitEdge();
	//bool hitZombie();

	int position();
	int row;
};
