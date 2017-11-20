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

int currentTime();//gets time in milliseconds since program start

static GameHandler game;

void main()
{
	//gameconsole.Initialize(vec2(120, 200), "Plants vs Zombies");//idk what this is

	srand(time(NULL));//set seed for random number generation

	const int FRAME_RATE = 2;//number of frames per second for display
	const int FRAME_TIME = 1000 / FRAME_RATE;//minimum time between each frame in milliseconds

	clock_t previousTime;//keeps track of the time that the last frame ran at

	previousTime = currentTime();//initializing previousTime

	game.initialize(currentTime());//initialize the game state

	PlaySound("assets/04-grasswalk.wav", NULL, SND_LOOP | SND_ASYNC);//start playing background music

	//main game loop
	while (true) {

		//updating the game state
		game.update(currentTime());//passing in currently elapsed time in ms

		if (currentTime() - previousTime >= FRAME_TIME) {//draws to the screen on each frame of the game

			previousTime = currentTime();//set previousTime to the time the previous frame (relative to the next frame) ran

			//rendering objects to the screen
			game.render();
		}

	}//main game loop
	
}//void main

int currentTime() {
	return clock() / (double)CLOCKS_PER_SEC * 1000;
}