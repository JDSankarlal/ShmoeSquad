#include "Windows.h"
#include <ctime>
#include "GameHandler.h"
#include "Events.h"

#pragma comment(lib, "Winmm.lib")//for playing the music

int currentTime();//gets time in milliseconds since program started

HANDLE buffer1;//handle for the buffer for rendering into

HANDLE wHnd;//handle for standard Windows Console output
HANDLE rHnd;//handle for standard Windows Console intput

static GameHandler game;//the game instance

void main()
{
	//Setting up screen buffer
	buffer1 = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	// Setting up handles for reading/writing
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);

	// Changing the window title
	SetConsoleTitle(TEXT("Plants VS Zombies!?"));

	// Setting window size
	SMALL_RECT windowSize = { 0, 0, 133, 48 };//{.Left, .Top, .Right, .Bottom}
	// Change the console window size:
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);

	// Creating a COORD to hold the buffer size
	COORD bufferSize = { 134, 49 };
	// Change the internal buffer size:
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	SetConsoleScreenBufferSize(buffer1, bufferSize);

	CHAR_INFO charBuffer[134 * 49];//buffer for copying rendering buffer into active buffer

	srand(time(NULL));//set seed for random number generation

	const int FRAME_RATE = 60;//number of frames per second for display
	const int FRAME_TIME = 1000 / FRAME_RATE;//minimum time between each frame in milliseconds

	clock_t previousTime;//keeps track of the time that the last frame ran at

	DWORD sleepTime;//used by Windows Sleep() function, time in milliseconds

	previousTime = currentTime();//initializing previousTime

	game.loadSprites();//must be called before initialize, loads sprite data into memory

	while (true) {

		game.mainMenu();

		game.initialize(currentTime());//initialize the game state

		PlaySound("assets/04-grasswalk.wav", NULL, SND_LOOP | SND_ASYNC);//start playing background music

		//main game loop
		while (true) {
			if (game.lose == true) {//exit game loop
				break;
			}
			//updating game state
			game.update(currentTime());//passing in currently elapsed time in ms

			//rendering graphics
			if (currentTime() - previousTime >= FRAME_TIME) {//draws to the screen on each frame of the game

				game.render(buffer1);

				ReadConsoleOutput(buffer1, charBuffer, bufferSize, { 0,0 }, &windowSize);
				WriteConsoleOutput(wHnd, charBuffer, bufferSize, { 0,0 }, &windowSize);

				previousTime = currentTime();//set previousTime to the time the previous frame (relative to the next frame) ran
			}
			else {
				sleepTime = FRAME_TIME - (currentTime() - previousTime);
				Sleep(sleepTime);//sleep for remainder of time until next frame
			}

		}//main game loop

		if (game.runProgram == false) {//exit program
			break;
		}

	}//main menu loop
	
}//void main

int currentTime() {
	return clock() / (double)CLOCKS_PER_SEC * 1000;
}