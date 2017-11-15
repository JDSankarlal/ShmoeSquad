#include "console.h"
#include "GameHandler.h"
#include <iostream>
#include <ctime>


using std::cout;
using std::cin;
using std::string;
using std::endl;


static GameHandler game;
static Console gameconsole;
void main()

{
	game.printDisplay();
	clock_t SUN_TIME; 
	SUN_TIME = clock(); 
	clock_t ZOMBIE_TIME;
	ZOMBIE_TIME = clock();
	while (true) {
	 //Program run time at this point saved in variable GAME_TIME
	//gameconsole.Initialize(vec2(120, 200), "Plants vs Zombies");
	//cout << GAME_TIME << endl;

	if (((clock() - SUN_TIME) / CLOCKS_PER_SEC) >= 10.0f)
	{
		game.createSun();
		SUN_TIME = clock();
	}
	
	if (((clock() - ZOMBIE_TIME) / CLOCKS_PER_SEC) >= 15.0f)
	{
		game.spawnZombie();
		ZOMBIE_TIME = clock();
	}
	}
	
}