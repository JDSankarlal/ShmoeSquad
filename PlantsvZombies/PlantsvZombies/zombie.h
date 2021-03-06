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

	enum Type {
		NORMAL,
		PYLON
	};
	bool isEating;

	int deathTime = -1;//used for delaying killing the zombie to after it's finished it's death animation
	int deathDelay = 0;//the delay between when the zombie is detected to die and when it actually dies

	int dmg = 1;//amount of damge dealt with each hit
	int dmgInterval = 1000;//interval at which zombie hits plant while colliding, 1s
	int dmgTime = -1;//time at which zombie started eating plant


	int health;//zombie's current hp
	int halfHP;


	State getState();

	Type getType();

	void defaultAnimation();
	void hurtAnimation(vector<vector<string>>* spriteData);
	void eatingAnimation(vector<vector<string>>* spriteData, vector<vector<string>>* spriteData2, int time);
	void deathAnimation(vector<vector<string>>* spriteData, int time);//called when zombie's hp reaches 0, sets state to dead and starts death animation
	bool killZombie(int time);//check if death animation is over and actually kill the zombie
	void takeDamage(int dmg, int time);//change colour of sprite so it flashes when taking damage

	int dealDamage(int time);
	
	bool endCollision();

protected:
	State state;
	Type type;
};
