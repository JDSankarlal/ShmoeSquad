#pragma once
#include "Sprite.h"
class Mower :
	public Sprite
{
public:
	Mower();
	Mower(vector<vector<string>>* spriteData, int time);
	~Mower();

	enum State {
		WAITING,//default state
		ACTIVATED//when a zombies reaches the end of a row (when it collides with the lawnmower)
	};

	int row;//the row the mower is in

	void defaultAnimation();

	void activate(int time);

private:
	State state;
};
