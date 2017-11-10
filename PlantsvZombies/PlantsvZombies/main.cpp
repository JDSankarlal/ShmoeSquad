#include<iostream>
#include <string>
#include <ctime>

using std::endl;
using std::cout;
using std::cin;
using std::string;

int frameCount = 0;//number or frames that have elapsed

int getClock();

void main()
{
	const int FRAME_RATE = 1;//number of frames per second
	const int FRAME_TIME = 1000 / FRAME_RATE;//minimum time between each frame in milliseconds

	clock_t currentTime;//keeps track of the current time
	clock_t previousTime;//keeps track of the time that the last frame ran at


	currentTime = getClock();
	previousTime = currentTime;

	while (true) {//main loop

		currentTime = getClock();//set currentTime to the currently elasped time

		if (currentTime - previousTime >= FRAME_TIME) {

			previousTime = currentTime;//set previousTime to the time the previous frame ran
			frameCount++;

			//updateGame();//next frame of game is run
		}
	}
}

int getClock() {
	return clock() / (double)CLOCKS_PER_SEC * 1000;
}