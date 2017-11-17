#include "GameHandler.h"
#include <iostream>
#include <ctime>
#include "Events.h"
#include "Sprite.h"
#include "Windows.h"
#include "plant.h"

#pragma comment(lib, "Winmm.lib")

using std::cout;
using std::cin;
using std::string;
using std::endl;


static GameHandler game;


void main()

{
	game.printDisplay();
	game.spawnZombie();
	game.printZombies();
	clock_t SUN_TIME,ZOMBIE_TIME,WORLD_CLOCK;  //Saves two seperate time variables at runtime, modifies each individually below
	SUN_TIME = clock(); 
	ZOMBIE_TIME = clock();
	WORLD_CLOCK = clock();
	PlaySound("C:\\Users\\100658473\\Documents\\ShmoeSquad\\PlantsvZombies\\PlantsvZombies\\04-grasswalk.wav", NULL, SND_LOOP | SND_ASYNC);

	/*while (true) {

	 //Program run time at this point saved in variable GAME_TIME
	//gameconsole.Initialize(vec2(120, 200), "Plants vs Zombies");
	//cout << GAME_TIME << endl;

	if (((clock() - SUN_TIME) / CLOCKS_PER_SEC) >= 1.0f)  //Spawns a sun from SKY every 10 seconds. Will have to figure out how to spawn it every 10 local seconds relative to individual sunflowers spawn time
	{
		
		game.createSun();
		SUN_TIME = clock();
	}
	
	if (((clock() - ZOMBIE_TIME) / CLOCKS_PER_SEC) >= 2.0f) //World spawns a zombie every 15 seconds, will have to adjust time as the world clock increases.
	{
		game.spawnZombie();
		ZOMBIE_TIME = clock();
	}
	

	}*/

	system("pause");
	
}