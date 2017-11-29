#include "Windows.h"
#include <ctime>
#include "GameHandler.h"
#include "Events.h"

#pragma comment(lib, "Winmm.lib")//for playing sound

int currentTime();//gets time in milliseconds since program start

void fullscreen();//puts program in fullscreen mode

HANDLE buffer1;

HANDLE wHnd;
HANDLE rHnd;

static GameHandler game;

void main()
{
	//Setting up screen buffers
	buffer1 = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//buffer2 = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

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

	CHAR_INFO charBuffer[134 * 45];

	srand(time(NULL));//set seed for random number generation

	const int FRAME_RATE = 60;//number of frames per second for display
	const int FRAME_TIME = 1000 / FRAME_RATE;//minimum time between each frame in milliseconds

	clock_t previousTime;//keeps track of the time that the last frame ran at

	DWORD sleepTime;

	previousTime = currentTime();//initializing previousTime

	game.loadSprites();//must be called before initialize, loads sprite data into memory
	game.initialize(currentTime());//initialize the game state

	PlaySound("assets/04-grasswalk.wav", NULL, SND_LOOP | SND_ASYNC);//start playing background music

	//main game loop
	while (true) {

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
	
}//void main

int currentTime() {
	return clock() / (double)CLOCKS_PER_SEC * 1000;
}

void fullscreen()
{
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

