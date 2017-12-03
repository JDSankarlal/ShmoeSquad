#pragma once
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <ctime>
#include <vector>
#include <string>
#include <Windows.h>
#include <iostream>
#include "Zombie.h"
#include "PylonZombie.h"
#include "Sunflower.h"
#include "Peashooter.h"
#include "Wallnut.h"
#include "Bullet.h"
#include "Mower.h"
#include "Events.h"
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
	void checkPlantBuy(int time);
	void placingPlant(int time);

	bool isPlacingPlant = false;

	void placePlant(COORD pos, Plant::plantType type, int time);//places a plant at given coordinates
	void spawnBullet(Plant*, int time);//creates a bullet for the passed in plant
	void spawnZombie(int time);//creates a zombie in a random row
	void createSun(int num);//adds a certain amount of sun to the player's sun count
	//void spawnSun(Plant*, int time);//creates a sun for the passed in plant, unused for now

	void checkZombieSpawn(int time);
	void checkSunSpawn(int time);

	void cls(HANDLE buffer, int colour);//clears the screen
	void printString(HANDLE buffer, string string, COORD position, int colour);
	void fullscreen();//puts program in fullscreen mode

	void mainMenu();
	void howToPlay();
	void gameFinished();
	void exitGame();
	void checkPause();
	void creditsDisplay();

	int randNum(int min, int max);//genrates a random number in a range

	vector<vector<string>> getSprite(string fileName);//reads in ascii data for a sprite and stores it in a vector, of vectors, of strings
	void loadSprites();//loads all the sprites into memory on program start


	//VARIABLES
	int numChosenPlants = 0;
	Plant** chosenPlants = NULL;//the list of plants that the player can buy
	Plant* selectedPlant = NULL;

	vector<Zombie*> zombies;//list of all current zombies
	vector<Plant*> plants;//list of all current sprites
	vector<Bullet*> bullets;//list of all current bullets
	vector<Mower*> mowers;//list of all lawnmowers
	//vector<Sun*> suns;//list of all current suns, unused for now

	Sprite grid;
	Sprite square;
	Sprite squareBar;
	Sprite bar;//sprites for the grid and plant bar
	Sprite menuMain;
	Sprite gameOver;
	Sprite howPlay;
	Sprite pauseScreen;
	Sprite credits;

	Sprite shovelDisplay;

	bool lose = false;
	bool runProgram = true;

	int pauseTime = 0;//total pause time for game since start

	int sunCount;//amount of sun player has
	int sunAdded;//amount of sun obtained this frame
	int displaySunAdded = 0;//used to print to the screen only
	int displaySunAddedTime;//time at which sun added started displaying
	int displaySunAddedLength = 3000;//amount of time added sun is displayed for

	int zombieInterval;//the interval in ms that zombies spawn, every 27s
	int zombieIncreaseInterval = 23000;//The interval that the zombie spawn rate increases at
	float zombieIncreaseAmount = 0.925;//the degree to which the zombie spawn rate increases at each interval
	int previousIncreaseTime = -1;
	int previousZombieTime;//stores last time a zombie was spawned
	int numSpawn = 1;//number of zombies to spawn at each interval
	int numSpawnIncreaseInterval = 90000;//interval that number of zombies increases at
	int previousNumSpawnIncrease = -1;//last time number of zombies increased
	//int numSpawnIncreaseTracker = 0;//used to determine when to increase number of zombies to spawn
	int startSpawningPylons;//time to start spawning pylon Zombies
	int pylonSpawnRate = 5;//every x zombies, spawn a pylon zombie
	int pylonSpawnIncrementor = pylonSpawnRate;//
	bool spawnFirstPylon = false;

	int previousRows[3] = { -1 };//previous 5 rows zombies have spawned in
	int incrementor = 0;//used for adding randomly generated numbers to next location in previousRows array

	int sunInterval = 11000;//interval suns spawn at, spawn a sun every 11s
	int previousSunTime;//last time a sun spawned

	int boxMoveTime = -1; //Time since box last moved
	int boxMoveInterval = 140; //The time in which the box can move

	int sunflowerCooldown = 0;
	int peashooterCooldown = 0;
	int wallnutCooldown = 0;
	bool shovel = false;

	int currentSunflowerCooldown = 0;
	int currentPeashooterCooldown = 0;
	int currentWallnutCooldown = 0;

	int startTime = 0;
	float surviveTime = 0.0f;


	//SPRITE DATA
	vector<vector<string>> defaultSprite;
	vector<vector<string>> barSprite;
	vector<vector<string>> bulletSprite;
	vector<vector<string>> gridSprite;
	vector<vector<string>> lawnmowerSprite;
	vector<vector<string>> peashooterSprite;
	vector<vector<string>> peashooter_shootingSprite;
	vector<vector<string>> selectionsquareSprite;
	vector<vector<string>> selectionsquarebarSprite;
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
	vector<vector<string>> zombiepylonSprite;
	vector<vector<string>> zombiepylon_dyingSprite;
	vector<vector<string>> zombiepylon_eatingSprite;
	vector<vector<string>> zombiepylon_hurtSprite;
	vector<vector<string>> zombiepylon_hurt_eatingSprite;
	vector<vector<string>> menu_Main;
	vector<vector<string>> game_Over;
	vector<vector<string>> how_Play;
	vector<vector<string>> shovelSprite;
	vector<vector<string>> pauseSprite;
	vector<vector<string>> creditsSprite;
};
