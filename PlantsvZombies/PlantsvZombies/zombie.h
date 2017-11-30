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
		HURT,//when health is below half
		DEAD//set to this when zombie health reaches 0
	};

	int deathTime = -1;//used for delaying killing the zombie to after it's finished it's death animation
	int deathDelay = 0;//the delay between when the zombie is detected to die and when it actually dies


	int health;//zombie's current hp
	int row;//the row the zombie is located in


	void setState(State);
	State getState();

	void defaultAnimation();
	void hurtAnimation(vector<vector<string>>* spriteData);
	void eatingAnimation(vector<vector<string>>* spriteData, vector<vector<string>>* spriteData2, int time);
	void deathAnimation(vector<vector<string>>* spriteData, int time);//called when zombie's hp reaches 0, sets state to dead and starts death animation
	bool killZombie(int time);//check if death animation is over and actually kill the zombie
	void takeDamage(int dmg, int time);//change colour of sprite so it flashes when taking damage

	
	bool endCollision();
	bool shot();
	int position();

private:
	State state;
};
