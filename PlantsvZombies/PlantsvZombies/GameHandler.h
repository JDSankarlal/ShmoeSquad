#pragma once
#include <cstdio>
#include <ctime>
#include <vector>
#include <string>
#include <Windows.h>
#include <iostream>
#include "Zombie.h"
#include "Sunflower.h"
#include "Peashooter.h"
#include "Wallnut.h"
#include "Bullet.h"
#include "Mower.h"
//#include "Sun.h"

using std::vector;
using std::string;

class GameHandler
{
public:
	GameHandler();
	~GameHandler();
	//FUNCTIONS
	void initialize(int time);//initializes game state

	void render(HANDLE buffer);//draws everything to the screen
	void printBar(HANDLE buffer);//prints the plant buy bar
	void printDisplay(HANDLE buffer);//prints the UI and Grid
	void printPlants(HANDLE buffer);//prints all plants
	void printBullets(HANDLE buffer);//prints all bullets
	void printZombies(HANDLE buffer);//prints all zombies
	void printMowers(HANDLE buffer);//prints all lawnmowers
	//void printSuns(HANDLE buffer);//prints all suns, unused for now

	void deletePlants();//deletes all plants
	void deleteBullets();//deletes all bullets
	void deleteZombies();//deletes all zombies
	void deleteMowers();//deletes all lawnmowers
	//void clearSuns();//unused for now

	void update(int time);//updates the state of plants, zombies, bullets, and suns
	//void collisions();
	void checkPlantBuy();

	void placePlant(COORD pos, Plant::plantType type, int time);//places a plant at given coordinates
	void spawnBullet(Plant*, int time);//creates a bullet for the passed in plant
	void spawnZombie(int time);//creates a zombie in a random row
	void createSun(int num);//adds a certain amount of sun to the player's sun count
	//void spawnSun(Plant*, int time);//creates a sun for the passed in plant, unused for now

	void checkZombieSpawn(int time);
	void checkSunSpawn(int time);

	void cls(HANDLE buffer, int colour);//clears the screen
	void printString(HANDLE buffer, string string, COORD position);
	void fullscreen();//puts program in fullscreen mode

	int randNum(int min, int max);//genrates a random number in a range

	vector<vector<string>> getSprite(string fileName);//reads in ascii data for a sprite and stores it in a vector, of vectors, of strings
	void loadSprites();//loads all the sprites into memory on program start


	//VARIABLES
	int numChosenPlants = 0;
	Plant** chosenPlants = 0;//the list of plants that the player can buy

	vector<Zombie*> zombies;//list of all current zombies
	vector<Plant*> plants;//list of all current sprites
	vector<Bullet*> bullets;//list of all current bullets
	vector<Mower*> mowers;//list of all lawnmowers
	//vector<Sun*> suns;//list of all current suns, unused for now

	Sprite grid;
	Sprite bar;//sprites for the grid and plant bar

	int sunCount;//amount of sun player has
	int zombieInterval;//the interval in ms that zombies spawn
	int sunInterval;//interval suns spawn at
	int previousZombieTime;//stores last time a zombie was spawned
	int previousSunTime;//last time a sun spawned


	//SPRITE DATA
	vector<vector<string>> defaultSprite;
	vector<vector<string>> barSprite;
	vector<vector<string>> bulletSprite;
	vector<vector<string>> gridSprite;
	vector<vector<string>> lawnmowerSprite;
	vector<vector<string>> peashooterSprite;
	vector<vector<string>> peashooter_shootingSprite;
	vector<vector<string>> selectionsquareSprite;
	vector<vector<string>> sunflowerSprite;
	vector<vector<string>> sunflower_shineSprite;
	//vector<vector<string>> sunSprite;//unused for now
	vector<vector<string>> wallnutSprite;
	vector<vector<string>> wallnut_hurtSprite;
	vector<vector<string>> zombieSprite;
	vector<vector<string>> zombie_dyingSprite;
	vector<vector<string>> zombie_eatingSprite;
	vector<vector<string>> zombie_hurtSprite;
	vector<vector<string>> zombie_hurt_eatingSprite;
};
