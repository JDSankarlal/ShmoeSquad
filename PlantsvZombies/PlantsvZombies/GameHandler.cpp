#include "GameHandler.h"

using std::endl;
using std::cout;
using std::vector;

clock_t GAME_TIME;
GameHandler::GameHandler()
{
	initialize(0);
}

GameHandler::~GameHandler()
{
}

void GameHandler::initialize(int time) {
	sunCount = 50;
	zombieInterval = 8000;//spawn a zombie every 8s
	sunInterval = 30000;//spawn a sun every 30s
	previousZombieTime = time;
	previousSunTime = time;

	bar.getData("assets/bar.txt");
	bar.setPosition({ 13,0 });
	grid.getData("assets/grid2.txt");
	grid.setPosition({ 13,10 });

	//initializing the chosenPlants array with the default set of plants you can buy
	chosenPlants[0] = new Sunflower;
	chosenPlants[1] = new Peashooter;
	chosenPlants[2] = new Wallnut;

	//placing plants for testing purposes
	COORD pos = grid.getPosition();
	placePlant({ pos.X + 3, pos.Y + 1 }, Plant::SUNFLOWER);
	pos.Y += 6;
	placePlant({ pos.X + 3, pos.Y + 1 }, Plant::PEASHOOTER);
	pos.Y += 6;
	placePlant({ pos.X + 3, pos.Y + 1 }, Plant::WALLNUT);
}

void GameHandler::render() {
	cls();
	printDisplay();
	printPlants();
	printZombies();
	printBullets();
	//printSuns();
}

void GameHandler::printBar() {//will take in a list of Plants, draw one of each in each square
	bar.draw();//draw the actual bar
	COORD pos = bar.getPosition();
	pos.X += 3;
	pos.Y += 1;
	for (SHORT i = 0; i < 3; i++) {//drawing plants inside of the bar
		chosenPlants[i]->setPosition({pos.X + i * 12, pos.Y});
		chosenPlants[i]->draw();
	}
}

void GameHandler::printDisplay()
{
	printBar();
	grid.draw();
	//displays the player's sun count
	COORD pos = grid.getPosition();
	pos.Y -= 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("Sun: %i \r", sunCount);
}

void GameHandler::printPlants() {
	for (std::vector<Plant>::iterator it = plants.begin(); it != plants.end(); ++it) {
		it->draw();
	}
}

void GameHandler::printBullets() {
	for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
		it->draw();
	}
}

void GameHandler::printSuns() {
	for (std::vector<Sun>::iterator it = suns.begin(); it != suns.end(); ++it) {
		it->draw();
	}
}

void GameHandler::printZombies() {
	for (std::vector<Zombie>::iterator it = zombies.begin(); it != zombies.end(); ++it) {
		it->draw();
	}
}

void GameHandler::update(int time) {
	checkZombieSpawn(time);
	checkSunSpawn(time);

	for (std::vector<Plant>::iterator it = plants.begin(); it != plants.end(); ++it) {//update plants
		if (it->shoot(time) == true) {//check if each plant is shooting on the current frame
			if (it->getType() == Plant::PEASHOOTER) {//peashooters will shoot bullets
				spawnBullet(*it);
			}
			else if (it->getType() == Plant::SUNFLOWER) {//sunflowers will create sun instead of shooting
				spawnSun(*it);
			}
		}
	}
	for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it) {//update bullets
		it->move(time);//bullets move a certain distance each frame
	}
	for (std::vector<Sun>::iterator it = suns.begin(); it != suns.end(); it++) {//update suns
		if (it->updateLife() == false) {//if the sun's lifeTime is 0
			//suns.erase(it);
		}
		else {
			//it++;
		}
	}
	for (std::vector<Zombie>::iterator it = zombies.begin(); it != zombies.end(); ++it) {//update zombies
		it->move(time);//zombies move a certain distance each frame
	}
}

void GameHandler::checkZombieSpawn(int time) {
	if (time - previousZombieTime >= zombieInterval) {
		spawnZombie();
		previousZombieTime = time;
	}
}

void GameHandler::checkSunSpawn(int time) {
	if (time - previousSunTime >= sunInterval) {
		createSun();
		previousSunTime = time;
	}
}

void GameHandler::checkPlantBuy() {
}

void GameHandler::placePlant(COORD pos, Plant::plantType type) {
	Plant* plant = 0;
	if (type == Plant::PEASHOOTER) {
		plant = new Peashooter;//creates a new peashooter
	}
	else if (type == Plant::SUNFLOWER) {
		plant = new Sunflower;//creates a new sunflower
	}
	else if (type == Plant::WALLNUT) {
		plant = new Wallnut;//creates a new wallnut
	}
	plant->setPosition(pos);

	plants.push_back(*plant);//adds newly created plant to the list
}

void GameHandler::spawnBullet(Plant shooter) {
	COORD spawnPos = shooter.getPosition();
	spawnPos.X += 7;
	spawnPos.Y += 1;

	Bullet* bullet = new Bullet;//creates a new bullet
	bullet->setPosition(spawnPos);

	bullets.push_back(*bullet);//adds newly created bullet to the list
}

void GameHandler::spawnSun(Plant flower) {
	COORD spawnPos = flower.getPosition();
	spawnPos.X += 3;
	spawnPos.Y -= 1;

	Sun* sun = new Sun;//creates a new sun
	sun->setPosition(spawnPos);

	suns.push_back(*sun);//adds newly created bullet to the list
	createSun();
}

void GameHandler::spawnZombie() {
	COORD gridPos = grid.getPosition();
	gridPos.Y += 1;
	COORD spawnPos;
	spawnPos.X = gridPos.X + 110;
	spawnPos.Y = gridPos.Y + randNum(0, 5) * 6;

	Zombie* zombie = new Zombie;//creates a new zombie
	zombie->setPosition(spawnPos);

	zombies.push_back(*zombie);//adds newly created zombie to the list

}

void GameHandler::createSun() {//Every x seconds we want to create sun and add it to the player's sun counter.
	sunCount += 50;
}

void GameHandler::cls()//This is used insted of system("cls")
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 };    // home for the cursor 
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	// Get the number of character cells in the current buffer. 

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Fill the entire screen with blanks.

	if (!FillConsoleOutputCharacter(hConsole,        // Handle to console screen buffer 
		(TCHAR) ' ',     // Character to write to the buffer
		dwConSize,       // Number of cells to write 
		coordScreen,     // Coordinates of first cell 
		&cCharsWritten))// Receive number of characters written
	{
		return;
	}

	// Get the current text attribute.

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}

	// Set the buffer's attributes accordingly.

	if (!FillConsoleOutputAttribute(hConsole,         // Handle to console screen buffer 
		csbi.wAttributes, // Character attributes to use
		dwConSize,        // Number of cells to set attribute 
		coordScreen,      // Coordinates of first cell 
		&cCharsWritten)) // Receive number of characters written
	{
		return;
	}

	// Put the cursor at its home coordinates.

	SetConsoleCursorPosition(hConsole, coordScreen);
}

int GameHandler::randNum(int min, int max) {//takes in the minimum value and maximum value for random number to be generated
	int num = min + (rand() % max - min);
	return num;
}