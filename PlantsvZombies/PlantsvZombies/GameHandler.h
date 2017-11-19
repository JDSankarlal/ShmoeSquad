#pragma once
#include <cstdio>
#include <ctime>
#include <vector>
#include <Windows.h>
#include <iostream>
#include "Zombie.h"
#include "Sunflower.h"
#include "Peashooter.h"
#include "Wallnut.h"
#include "Bullet.h"
#include "Sun.h"
using std::vector;

class GameHandler
{
public:
	GameHandler();
	~GameHandler();

	void initialize();//initializes game state
	void printBar();//prints the plant buy bar
	void printDisplay();//prints the UI and Grid
	void printPlants();//prints all plants
	void printBullets();//prints all bullets
	void printSuns();//prints all suns
	void printZombies();//prints all zombies
	void update(int time);
	void checkPlantBuy();
	void placePlant(COORD pos, Plant::plantType type);//places a plant at given coordinates
	void spawnBullet(Plant);
	void spawnSun(Plant);
	void spawnZombie();
	void createSun();
	//void erase(int x, int y, int w);//not needed
	void cls();//clears the screen
	int randNum(int min, int max);//genrates a random number in a range

	Plant* chosenPlants[3];//the list of plants that the player can buy

	vector<Zombie> zombies;//list of all current zombies
	vector<Plant> plants;//list of all current sprites
	vector<Bullet> bullets;//list of all current bullets
	vector<Sun> suns;//list of all current suns
	Sprite grid, bar;

	int sunCount;
};

