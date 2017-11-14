#include<iostream>
#include <string>
#include <ctime>
#include <stdlib.h>

using std::endl;
using std::cout;
using std::cin;
using std::string;

int frameCount = 0;//number or frames that have elapsed

int getClock();

//const int SIZE; //6 in your case
char grid[5][5] = { { '1','2','3','4','5' },
					{ '1','2','3','4','5' },
					{ '1','2','3','4','5' },
					{ '1','2','3','4','5' },
					{ '1','2','3','4','5' } };
int position[2] = { 2, 2 };

void main()
{

	system("Color 02");

	const int FRAME_RATE = 1;//number of frames per second
	const int FRAME_TIME = 1000 / FRAME_RATE;//minimum time between each frame in milliseconds

	clock_t currentTime;//keeps track of the current time
	clock_t previousTime;//keeps track of the time that the last frame ran at

	char plant = '*';
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (i == position[0] && j == position[1])
				cout << plant;
			else
				cout << grid[i][j];
			cout << " ";
		}
		cout << endl;
	}

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