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

HANDLE buffer1;
HANDLE buffer2;

HANDLE wHnd;
HANDLE rHnd;

static GameHandler game;

void main()
{
	//Setting up screen buffers
	buffer1 = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	buffer2 = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	// Set up the handles for reading/writing:
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);

	// Change the window title:
	SetConsoleTitle(TEXT("Plants VS Zombies!?"));

	// Set up the required window size:
	SMALL_RECT windowSize = { 0, 0, 133, 44 };//{.Left, .Top, .Right, .Bottom}
	// Change the console window size:
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);

	// Create a COORD to hold the buffer size:
	COORD bufferSize = { 134, 45 };
	// Change the internal buffer size:
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	SetConsoleScreenBufferSize(buffer1, bufferSize);
	SetConsoleScreenBufferSize(buffer2, bufferSize);

	srand(time(NULL));//set seed for random number generation

	const int FRAME_RATE = 60;//number of frames per second for display
	const int FRAME_TIME = 1000 / FRAME_RATE;//minimum time between each frame in milliseconds

	clock_t previousTime;//keeps track of the time that the last frame ran at

	previousTime = currentTime();//initializing previousTime

	game.initialize(currentTime());//initialize the game state

	PlaySound("assets/04-grasswalk.wav", NULL, SND_LOOP | SND_ASYNC);//start playing background music

	//SetConsoleActiveScreenBuffer(buffer2);

	int useBuffer = 1;//used for alternating between the screen buffers

	//main game loop
	while (true) {

		//updating the game state
		game.update(currentTime());//passing in currently elapsed time in ms

		if (currentTime() - previousTime >= FRAME_TIME) {//draws to the screen on each frame of the game
			//alternating which buffer the game is rendering to
			if (useBuffer == 1) {
				game.render(buffer1);
				SetConsoleActiveScreenBuffer(buffer1);
				useBuffer = 2;
			}
			else if (useBuffer == 2) {
				game.render(buffer2);
				SetConsoleActiveScreenBuffer(buffer2);
				useBuffer = 1;
			}
			previousTime = currentTime();//set previousTime to the time the previous frame (relative to the next frame) ran
		}

	}//main game loop
	
}//void main

int currentTime() {
	return clock() / (double)CLOCKS_PER_SEC * 1000;
}