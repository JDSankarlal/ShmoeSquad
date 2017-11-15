#include "console.h"
#include "GameHandler.h"
#include <iostream>

using std::cout;
using std::cin;
using std::string;
using std::endl;


static GameHandler game;
void main()
{
	game.printDisplay();
}