#include "console.h"
#include "GameHandler.h"
#include <iostream>
#include <ctime>
#include "Events.h"
#include "Sprite.h"

using std::cout;
using std::cin;
using std::string;
using std::endl;


static GameHandler game;
static Console gameconsole;
void main()

{
	Sprite zombie;
	zombie.init('%')->setPosition(COORD{ 10,10 });
	game.printDisplay();
	clock_t SUN_TIME,ZOMBIE_TIME,WORLD_CLOCK;  //Saves two seperate time variables at runtime, modifies each individually below
	SUN_TIME = clock(); 
	ZOMBIE_TIME = clock();
	WORLD_CLOCK = clock();

	while (true) {

	zombie.draw();
	 //Program run time at this point saved in variable GAME_TIME
	//gameconsole.Initialize(vec2(120, 200), "Plants vs Zombies");
	//cout << GAME_TIME << endl;

	if (((clock() - SUN_TIME) / CLOCKS_PER_SEC) >= 10.0f)  //Spawns a sun from SKY every 10 seconds. Will have to figure out how to spawn it every 10 local seconds relative to individual sunflowers spawn time
	{
		game.createSun();
		SUN_TIME = clock();
	}
	
	if (((clock() - ZOMBIE_TIME) / CLOCKS_PER_SEC) >= 15.0f) //World spawns a zombie every 15 seconds, will have to adjust time as the world clock increases.
	{
		game.spawnZombie();
		ZOMBIE_TIME = clock();
	}

	}
	
}