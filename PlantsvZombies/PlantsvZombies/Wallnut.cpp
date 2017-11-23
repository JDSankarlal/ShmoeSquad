#include "Wallnut.h"



Wallnut::Wallnut()
{
	type = WALLNUT;
	getData("assets/wallnut.txt");//gives it ASCII data
	health = 200;
}


Wallnut::~Wallnut()
{
}
