#pragma once
#include <cstdio>
#include <ctime>
#include <vector>
#include <Windows.h>
#include <iostream>
#include "Zombie.h"
#include "Plant.h"
using std::vector;

class GameHandler
{
public:
	void initGame();//initializes game state
	void printDisplay();//prints the UI and Grid
	void printPlants();//prints all plants
	void printZombies();//prints all zombies
	void checkPlantBuy();
	void createSun();
	void spawnZombie();
	void erase(int x, int y, int w);

	vector<Zombie> zombies;//list of all current zombies
	vector<Plant> plants;//list of all current sprites


	int sunCount;
	GameHandler();

	~GameHandler();
};

