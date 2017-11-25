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

	void initialize(int time);//initializes game state

	void render(HANDLE buffer);//draws everything to the screen
	void printBar(HANDLE buffer);//prints the plant buy bar
	void printDisplay(HANDLE buffer);//prints the UI and Grid
	void printPlants(HANDLE buffer);//prints all plants
	void printBullets(HANDLE buffer);//prints all bullets
	void printSuns(HANDLE buffer);//prints all suns
	void printZombies(HANDLE buffer);//prints all zombies

	void update(int time);//updates the state of plants, zombies, bullets, and suns
	void checkZombieSpawn(int time);
	void checkSunSpawn(int time);
	void checkPlantBuy();

	void placePlant(COORD pos, Plant::plantType type, int time);//places a plant at given coordinates
	void spawnBullet(Plant);//creates a bullet for the passed in plant
	void spawnSun(Plant, int time);//creates a sun for the passed in plant
	void spawnZombie();//creates a zombie in a random row
	void createSun();//adds a set amount of sun to the player's sun count

	void cls(HANDLE buffer, int colour);//clears the screen

	int randNum(int min, int max);//genrates a random number in a range

	int numChosenPlants = 0;
	Plant** chosenPlants = 0;//the list of plants that the player can buy

	vector<Zombie> zombies;//list of all current zombies
	vector<Plant> plants;//list of all current sprites
	vector<Bullet> bullets;//list of all current bullets
	vector<Sun> suns;//list of all current suns

	Sprite grid, bar;//sprites for the grid and plant bar

	int sunCount;
	int zombieInterval;//the interval in ms that zombies spawn
	int sunInterval;//interval suns spawn at
	int previousZombieTime;//stores last time a zombie was spawned
	int previousSunTime;//last time a sun spawned
	void collisions();
};

