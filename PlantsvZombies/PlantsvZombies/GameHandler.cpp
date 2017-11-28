#include "GameHandler.h"
#include "Zombie.h"

using std::endl;
using std::cout;
using std::vector;

//colour valuesfor drawing sprites
//foregroundColour_backgroundColour
#define white_black 0x000f
#define green_black 0x000a
#define dullGreen_black 0x0002
#define yellow_black 0x000e
#define turqoise_black 0x000b
#define dullTurqoise_black 0x000b - 0x0008
#define purple_black 0x000d
#define white_dullGreen 0x002f
#define white_grey 0x0080

GameHandler::GameHandler()
{
}

GameHandler::~GameHandler()
{
}

void GameHandler::initialize(int time) {
	//clearing object lists
	zombies.clear();
	plants.clear();
	bullets.clear();
	suns.clear();

	//initializing variables for spawn timers
	sunCount = 50;
	zombieInterval = 8000;//spawn a zombie every 8s
	sunInterval = 30000;//spawn a sun every 30s
	previousZombieTime = time;
	previousSunTime = time;

	//setting acii data for grid and bar
	bar.setData(barSprite);
	bar.setPosition({ 13,0 });
	int* sequence = new int[2]{ 0, 1 };
	grid.setAnimation(sequence, 2, 1044);

	grid.setData(gridSprite);
	grid.setPosition({ 13,10 });
	sequence = new int[4]{ 0,1,2,1 };
	grid.setAnimation(sequence, 4, 1044);

	//setting what plants are in the plant buy Bar
	numChosenPlants = 3;
	chosenPlants = new Plant*[numChosenPlants];
	chosenPlants[0] = new Sunflower(sunflowerSprite, time);
	chosenPlants[1] = new Peashooter(peashooterSprite, time);
	chosenPlants[2] = new Wallnut(wallnutSprite, time);

	//placing plants in the plant buy bar
	COORD pos = bar.getPosition();
	pos.X += 2;
	pos.Y += 1;
	for (SHORT i = 0; i < numChosenPlants; i++) {//placing plants inside of the bar
		chosenPlants[i]->setPosition({ pos.X + i * 12, pos.Y });
	}

	//placing plants for testing purposes
	pos = grid.getPosition();
	placePlant({ pos.X + 2, pos.Y + 1 }, Plant::SUNFLOWER, time);
	pos.Y += 6;
	placePlant({ pos.X + 2, pos.Y + 1 }, Plant::PEASHOOTER, time);
	pos.Y += 6;
	placePlant({ pos.X + 2, pos.Y + 1 }, Plant::WALLNUT, time);
}

void GameHandler::render(HANDLE buffer) {
	cls(buffer, white_black);
	printDisplay(buffer);
	printPlants(buffer);
	printZombies(buffer);
	printBullets(buffer);
	printSuns(buffer);
}

void GameHandler::printBar(HANDLE buffer) {//will take in a list of Plants, draw one of each in each square
	bar.draw(buffer, white_black);//draw the actual bar
	for (SHORT i = 0; i < numChosenPlants; i++) {//drawing plants inside of the bar
		chosenPlants[i]->draw(buffer, white_black);
	}
}

void GameHandler::printDisplay(HANDLE buffer)
{
	printBar(buffer);
	grid.draw(buffer, white_black);
	//displays the player's sun count
	COORD pos = grid.getPosition();
	pos.Y -= 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("Sun: %i \r", sunCount);
}

void GameHandler::printPlants(HANDLE buffer) {
	for (std::vector<Plant>::iterator it = plants.begin(); it != plants.end(); ++it) {
		it->draw(buffer, green_black);
	}
}

void GameHandler::printBullets(HANDLE buffer) {
	for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
		it->draw(buffer, green_black);
	}
}

void GameHandler::printSuns(HANDLE buffer) {
	for (std::vector<Sun>::iterator it = suns.begin(); it != suns.end(); ++it) {
		it->draw(buffer, yellow_black);
	}
}

void GameHandler::printZombies(HANDLE buffer) {
	for (std::vector<Zombie>::iterator it = zombies.begin(); it != zombies.end(); ++it) {
		it->draw(buffer, turqoise_black);
	}
}

void GameHandler::update(int time) {
	checkZombieSpawn(time);
	checkSunSpawn(time);

	bar.updateAnimation(time);
	grid.updateAnimation(time);

	for (std::vector<Plant>::iterator it = plants.begin(); it != plants.end(); ++it) {//update plants
		it->updateAnimation(time);
		if (it->shoot(time) == true) {//check if each plant is shooting on the current frame
			if (it->getType() == Plant::PEASHOOTER) {//peashooters will shoot bullets
				spawnBullet(*it, time);
			}
			else if (it->getType() == Plant::SUNFLOWER) {//sunflowers will create sun instead of shooting
				spawnSun(*it, time);
			}
		}
	}
	for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it) {//update bullets
		it->updateAnimation(time);
		it->move(time);//bullets move a certain distance each frame
	}
	
	for (int i = 0; i<bullets.size(); i++) {//deleting bullets
		if (bullets[i].hitEdge())
		{
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}

	for (std::vector<Zombie>::iterator it = zombies.begin(); it != zombies.end(); ++it) {//update zombies
		it->updateAnimation(time);
		it->move(time);//zombies move a certain distance each frame
	}

	//collision detection
	for (int i = 0; i<zombies.size(); i++) {//*this is broken right now*
		if (zombies[i].getPosition().Y == bullets[i].getPosition().Y)//*There may not be the same number of zombies and bullets, use another nested loop to go through all the bullets*
		{
			zombies[i].health -= 20;
		}
		if (zombies[i].endCollision() || zombies[i].health <= 0)
		{
			zombies.erase(zombies.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < suns.size(); i++)//update suns
	{
		suns[i].updateAnimation(time);
		if (suns[i].updateLife(time)== false)
		{
			suns.erase(suns.begin() + i);
			i--;
		}
	}
}

void GameHandler::checkZombieSpawn(int time) {
	if (time - previousZombieTime >= zombieInterval) {
		spawnZombie(time);
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

void GameHandler::placePlant(COORD pos, Plant::plantType type, int time) {
	Plant* plant = 0;
	if (type == Plant::PEASHOOTER) {
		plant = new Peashooter(peashooterSprite, time);//creates a new peashooter
	}
	else if (type == Plant::SUNFLOWER) {
		plant = new Sunflower(sunflowerSprite, time);//creates a new sunflower
	}
	else if (type == Plant::WALLNUT) {
		plant = new Wallnut(wallnutSprite, time);//creates a new wallnut
	}
	plant->setPosition(pos);

	plants.push_back(*plant);//adds newly created plant to the list
}

void GameHandler::spawnBullet(Plant shooter, int time) {
	COORD spawnPos = shooter.getPosition();
	spawnPos.X += 7;
	spawnPos.Y += 1;

	Bullet* bullet = new Bullet(bulletSprite, time);//creates a new bullet
	bullet->setPosition(spawnPos);

	bullets.push_back(*bullet);//adds newly created bullet to the list
}

void GameHandler::spawnSun(Plant flower, int time) {
	COORD spawnPos = flower.getPosition();
	//spawnPos.X += 1;
	//spawnPos.Y -= 1;

	Sun* sun = new Sun(sunflower_shineSprite, time);//creates a new sun
	sun->setPosition(spawnPos);

	suns.push_back(*sun);//adds newly created sun to the list
	createSun();
}

void GameHandler::spawnZombie(int time) {
	COORD gridPos = grid.getPosition();
	gridPos.Y += 1;
	COORD spawnPos;
	spawnPos.X = gridPos.X + 110;
	spawnPos.Y = gridPos.Y + randNum(0, 5) * 6;

	Zombie* zombie = new Zombie(zombieSprite, time);//creates a new zombie
	zombie->setPosition(spawnPos);

	zombies.push_back(*zombie);//adds newly created zombie to the list

}

void GameHandler::createSun() {//Every x seconds we want to create sun and add it to the player's sun counter.
	sunCount += 50;
}

/*void GameHandler::collisions(Zombie zombie) {//make this a function member of Sprite, a general checkCollision function: sprite1.checkCollision(sprite2);
	//if zombie collides with plant
	if (zombie.endCollision()) {

	}// If Zombie collides with end, found in Zombie.cpp and Zombie.h
	//if zombie collides with bullet
	Bullet hitEdge(); //if bullet collides with end of map found in Bullet.h and Bullet.cpp
}*/

void GameHandler::cls(HANDLE buffer, int colour)//This is used instead of system("cls")
{
	DWORD charsWritten;
	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	DWORD consoleSize;

	// Get the number of character cells in the current buffer
	GetConsoleScreenBufferInfo(buffer, &bufferInfo);

	consoleSize = bufferInfo.dwSize.X * bufferInfo.dwSize.Y;

	// Fill the buffer with blanks
	FillConsoleOutputCharacter(buffer,	// Handle to console screen buffer 
		(TCHAR) ' ',	// Character to write to the buffer
		consoleSize,	// Number of cells to write 
		{ 0,0 },	// Coordinates of first cell 
		&charsWritten);// Receive number of characters written

	FillConsoleOutputAttribute(buffer,	// Handle to console screen buffer 
		colour,	// Character attributes to use
		consoleSize,	// Number of cells to set attribute 
		{ 0,0 },	// Coordinates of first cell 
		&charsWritten);	// Receive number of characters written
}

int GameHandler::randNum(int min, int max) {//takes in the minimum value and maximum value for random number to be generated
	int num = min + (rand() % max - min);
	return num;
}

//**WARNING** all text files MUST end in a new line containing "new_frame" only
vector<vector<string>> GameHandler::getSprite(string fileName) {
	vector<vector<string>> asciiData;

	ifstream file;
	file.open(fileName);
	if (!file) {//if file wasn't opened successfully
		std::cout << "File " << fileName << " not found!";
		std::cin.ignore(1000, '\n');
		std::cin.get();
	}
	else {
		file >> std::noskipws;//tells it not to skip white space while scanning file
		string s;
		vector<string> fileData;//a vector of strings, used to store sprite data
		while (getline(file, s)) {
			if (s == "new_frame") {
				asciiData.push_back(fileData);//adding each line from the file into a vector of strings
				fileData.clear();
			}
			else {
				fileData.push_back(s);//adding each line from the file into a vector of strings
			}
		}
	}
	file.close();

	return asciiData;
}

void GameHandler::loadSprites() {
	defaultSprite = getSprite("assets/default.txt");
	barSprite = getSprite("assets/bar2.txt");
	bulletSprite = getSprite("assets/bullet.txt");
	gridSprite = getSprite("assets/lawn.txt");
	peashooterSprite = getSprite("assets/peashooter.txt");
	sunflowerSprite = getSprite("assets/sunflower.txt");
	sunflower_shineSprite = getSprite("assets/sunflower_shine.txt");
	wallnutSprite = getSprite("assets/wallnut.txt");
	zombieSprite = getSprite("assets/zombie.txt");
}