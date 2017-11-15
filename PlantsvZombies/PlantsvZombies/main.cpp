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
	clock_t GAME_TIME; 
	GAME_TIME = clock(); 
	while (true) {
	 //Program run time at this point saved in variable GAME_TIME
	//gameconsole.Initialize(vec2(120, 200), "Plants vs Zombies");
	//cout << GAME_TIME << endl;
	if (((clock() - GAME_TIME) / CLOCKS_PER_SEC) >= 5.0f)
	{
		game.createSun();
		GAME_TIME = clock();

	}

	}
	
}