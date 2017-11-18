#include "GameHandler.h"

using std::endl;
using std::cout;
using std::vector;


clock_t GAME_TIME;
GameHandler::GameHandler()
{
	sunCount = 50;
}


GameHandler::~GameHandler()
{
}

void GameHandler::initialize() {
	grid.getData("assets/grid.txt");
	grid.setPosition({ 0,9 });
	bar.getData("assets/bar.txt");
	bar.setPosition({ 0,0 });
}


void GameHandler::printDisplay()
{
	bar.draw();
	grid.draw();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 40 });//displays sun
	printf("Sun: %i \r", sunCount);
}

void GameHandler::printPlants() {
	for (std::vector<Plant>::iterator it = plants.begin(); it != plants.end(); ++it) {
		//it->updatePosition();
		it->draw();
	}
}

void GameHandler::printBullets() {
	for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
		it->draw();
	}
}

void GameHandler::printZombies() {//prints all zombies to the screen
	for (std::vector<Zombie>::iterator it = zombies.begin(); it != zombies.end(); ++it) {
		it->draw();
	}
}

void GameHandler::update(int time) {
	for (std::vector<Plant>::iterator it = plants.begin(); it != plants.end(); ++it) {
		if (it->shoot(time) == true) {
			spawnBullet(*it);
		}
	}
	for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
		it->updatePosition();
	}
	for (std::vector<Zombie>::iterator it = zombies.begin(); it != zombies.end(); ++it) {
		it->updatePosition();
	}
}

void GameHandler::checkPlantBuy() {



}

void GameHandler::placePlant(COORD pos) {
	Plant* plant = new Plant;//creates a new plant
	plant->getData("assets/peashooter.txt");//gives it ASCII data
	plant->setPosition(pos);

	plants.push_back(*plant);//adds newly created plant to the list
}

void GameHandler::spawnBullet(Plant shooter) {
	COORD spawnPos = shooter.getPosition();
	spawnPos.X += 10;
	spawnPos.Y += 1;

	Bullet* bullet = new Bullet;//creates a new bullet
	bullet->getData("assets/bullet.txt");//gives it ASCII data
	bullet->setPosition(spawnPos);

	bullets.push_back(*bullet);//adds newly created bullet to the list
}

void GameHandler::spawnZombie() {
	COORD spawnPos;
	spawnPos.X = 110;
	spawnPos.Y = 10 + randNum(0, 5) * 6;

	Zombie* zombie = new Zombie;//creates a new zombie
	zombie->getData("assets/zombie.txt");//gives it ASCII data
	zombie->setPosition(spawnPos);

	zombies.push_back(*zombie);//adds newly created zombie to the list

}

void GameHandler::createSun() {
	//Every x seconds we want to create sun and add it to the player's sun counter.
	sunCount += 25;
	//printf("%i\n", sunCount);
	//std::cout << sunCount << std::endl;
}

void GameHandler::erase(int y, int x, int w)
{
	DWORD l;
	for (SHORT i = 0; i < 40; i++) {
		FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', w, { (SHORT)x,(SHORT)y + i }, &l);
	}
}

void GameHandler::cls()
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

int GameHandler::randNum(int min, int max) {
	int num = min + (rand() % max - min);
	return num;
}