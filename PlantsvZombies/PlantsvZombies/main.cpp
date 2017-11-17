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

int frameCount = 0;//number or frames that have elapsed

int getClock();//gets time in milliseconds since program start


void main()
{
	srand(time(NULL));

	game.printDisplay();

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
		game.printZombies();
		
	}*/

	const int FRAME_RATE = 2;//number of frames per second for display
	const int FRAME_TIME = 1000 / FRAME_RATE;//minimum time between each frame in milliseconds

	clock_t currentTime;//keeps track of the current time
	clock_t previousTime;//keeps track of the time that the last frame ran at

	currentTime = getClock();
	previousTime = currentTime;

	while (true) {//main loop

		currentTime = getClock();//set currentTime to the currently elasped time

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

		if (currentTime - previousTime >= FRAME_TIME) {//draws to the screen on each frame of the game

			previousTime = currentTime;//set previousTime to the time the previous frame ran
			frameCount++;

			game.cls();
			game.printDisplay();
			game.printZombies();
		}
	}
	
}

int getClock() {
	return clock() / (double)CLOCKS_PER_SEC * 1000;
}