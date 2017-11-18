#pragma once
#include <cstdio>
#include <ctime>
#include <vector>
#include <Windows.h>
#include <iostream>
#include "Zombie.h"
#include "Peashooter.h"
#include "Sunflower.h"
#include "Bullet.h"
using std::vector;

class GameHandler
{
public:
	void initialize();//initializes game state
	void printBar();//prints the plant buy bar
	void printDisplay();//prints the UI and Grid
	void printPlants();//prints all plants
	void printBullets();//prints all bullets
	void printZombies();//prints all zombies
	void update(int time);
	void checkPlantBuy();
	void placePlant(COORD pos);
	void spawnBullet(Plant);
	void spawnZombie();
	void createSun();
	void erase(int x, int y, int w);
	void cls();
	int randNum(int min, int max);

	Plant* chosenPlants[9];//the list of plants that the player can buy

	vector<Zombie> zombies;//list of all current zombies
	vector<Plant> plants;//list of all current sprites
	vector<Bullet> bullets;//list of all current bullets
	Sprite grid, bar;

	int sunCount;
	GameHandler();

	~GameHandler();
};

