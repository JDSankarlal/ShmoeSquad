#pragma once
#include "Sprite.h"

class Zombie : public Sprite
{
public:
	Zombie();
	Zombie(vector<vector<string>>* spriteData, int time);
	~Zombie();

	enum State {
		ALIVE,//default state
		DEAD//set to this when zombie hp reaches 0
	};

	int health;
	int row;

	int deathTime = -1;//used for delaying killing the zombie to after it's finished it's death animation
	int deathDelay = 0;//the delay between when the zombie is detected to die and when it actually dies

	void setState(State);
	State getState();

	void defaultAnimation();
	void hurtAnimation(vector<vector<string>>* spriteData);
	void deathAnimation(vector<vector<string>>* spriteData, int time);//called when zombie's hp reaches 0, sets state to dead and starts death animation
	void takeDamage(int time);//change colour of sprite so it flashes when taking damage

	
	bool endCollision();
	bool shot();
	int position();

private:
	State state;
};