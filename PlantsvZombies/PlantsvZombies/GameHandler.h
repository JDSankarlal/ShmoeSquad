#pragma once
class GameHandler
{
public:
	void printDisplay();
	void checkPlantBuy();
	void createSun();
	void countSun();
	void spawnZombie();
	void erase(int x, int y, int w);


	int sunCount;
	GameHandler();

	~GameHandler();
};

