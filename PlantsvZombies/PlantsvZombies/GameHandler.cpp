#include "GameHandler.h"
#include "Zombie.h"

using std::endl;
using std::cout;
using std::vector;

//colour values for drawing sprites
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
#define red_black 0x0004 + 0x0008
#define dullRed_black 0x0004

GameHandler::GameHandler()
{
}
GameHandler::~GameHandler()
{
}
//INITIALIZING OBJECTS
void GameHandler::initialize(int time) {
	//clearing object lists
	deleteZombies();
	deletePlants();
	deleteBullets();
	deleteMowers();
	//deleteSuns();

	//initializing variables for spawn timers
	sunCount = 50;
	zombieInterval = 8000;//spawn a zombie every 8s
	sunInterval = 30000;//spawn a sun every 30s
	previousZombieTime = time;
	previousSunTime = time;

	//setting ascii data for grid/lawn
	grid.setData(&gridSprite);
	grid.setPosition({ 13,10 });
	int* sequence = new int[4]{ 0,1,2,1 };
	grid.setAnimation(sequence, 4, 1000, time);

	//setting acii data for bar
	bar.setData(&barSprite);
	bar.setPosition({ 13,0 });
	//sequence = new int[2]{ 0, 1 };
	//bar.setAnimation(sequence, 2, 1000, time);

	//setting what plants are in the plant buy Bar
	numChosenPlants = 3;
	chosenPlants = new Plant*[numChosenPlants];
	chosenPlants[0] = new Sunflower(&sunflowerSprite, time);
	chosenPlants[1] = new Peashooter(&peashooterSprite, time);
	chosenPlants[2] = new Wallnut(&wallnutSprite, time);

	//placing plants in the plant buy bar
	COORD pos = bar.getPosition();
	pos.X += 2;
	pos.Y += 1;
	for (SHORT i = 0; i < numChosenPlants; i++) {//placing plants inside of the bar
		chosenPlants[i]->setPosition({ pos.X + i * 12, pos.Y });
		chosenPlants[i]->setDefaultColour(white_black);
	}

	//placing plants for testing purposes
	pos = grid.getPosition();
	placePlant({ pos.X + 2, pos.Y + 1 }, Plant::SUNFLOWER, time);
	pos.Y += 6;
	placePlant({ pos.X + 2, pos.Y + 1 }, Plant::PEASHOOTER, time);
	pos.Y += 6;
	placePlant({ pos.X + 2, pos.Y + 1 }, Plant::WALLNUT, time);

	//setting up lawnmowers
	pos = grid.getPosition();
	pos.X -= 12;
	pos.Y += 2;
	Mower* lawnmower;
	for (int i = 0; i < 5; i++) {
		lawnmower = new Mower(&lawnmowerSprite, time);
		lawnmower->setPosition(pos);
		//lawnmower->activate(time);//for testing
		mowers.push_back(lawnmower);
		pos.Y += 6;
	}
}


//RENDERING OBJECTS
void GameHandler::render(HANDLE buffer) {
	cls(buffer, white_black);
	printDisplay(buffer);
	printPlants(buffer);
	printZombies(buffer);
	printBullets(buffer);
	printMowers(buffer);
	//printSuns(buffer);
}

void GameHandler::printBar(HANDLE buffer) {//will take in a list of Plants, draw one of each in each square
	bar.draw(buffer);//draw the actual bar
	for (SHORT i = 0; i < numChosenPlants; i++) {//drawing plants inside of the bar
		chosenPlants[i]->draw(buffer);
	}
}

void GameHandler::printDisplay(HANDLE buffer)
{
	printBar(buffer);
	grid.draw(buffer);
	//displays the player's sun count
	COORD pos = grid.getPosition();
	pos.Y -= 2;

	string numSun = "Sun: " + std::to_string(sunCount);

	printString(buffer, numSun, pos, white_black);

	if (displaySunAdded > 0) {
		string sunObtained = " + " + std::to_string(displaySunAdded);
		printString(buffer, sunObtained, { pos.X + static_cast<SHORT>(numSun.size()), pos.Y }, yellow_black);
	}
}

void GameHandler::printPlants(HANDLE buffer) {
	for (std::vector<Plant*>::iterator it = plants.begin(); it != plants.end(); ++it) {
		(*it)->draw(buffer);
	}
}
void GameHandler::printBullets(HANDLE buffer) {
	for (std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
		(*it)->draw(buffer);
	}
}
void GameHandler::printZombies(HANDLE buffer) {
	for (std::vector<Zombie*>::iterator it = zombies.begin(); it != zombies.end(); ++it) {
		(*it)->draw(buffer);
	}
}
void GameHandler::printMowers(HANDLE buffer) {
	for (std::vector<Mower*>::iterator it = mowers.begin(); it != mowers.end(); ++it) {
		(*it)->draw(buffer);
	}
}
/*void GameHandler::printSuns(HANDLE buffer) {//unused for now
	for (std::vector<Sun*>::iterator it = suns.begin(); it != suns.end(); ++it) {
		(*it)->draw(buffer);
	}
}*/


//CLEARING OBJECTS
void GameHandler::deletePlants() {
	for (std::vector<Plant*>::iterator it = plants.begin(); it != plants.end(); ++it) {
		delete (*it);
	}
	plants.clear();
}
void GameHandler::deleteBullets() {
	for (std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
		delete (*it);
	}
	bullets.clear();
}
void GameHandler::deleteZombies() {
	for (std::vector<Zombie*>::iterator it = zombies.begin(); it != zombies.end(); ++it) {
		delete (*it);
	}
	zombies.clear();
}
void GameHandler::deleteMowers() {
	for (std::vector<Mower*>::iterator it = mowers.begin(); it != mowers.end(); ++it) {
		delete (*it);
	}
	mowers.clear();
}
/*void GameHandler::deleteSuns() {//unused for now
	for (std::vector<Sun*>::iterator it = suns.begin(); it != suns.end(); ++it) {
		delete (*it);
	}
	suns.clear();
}*/


//UPDATING OBJECTS
void GameHandler::update(int time) {
	if (time - displaySunAddedTime >= displaySunAddedLength) {
		displaySunAdded = 0;
	}
	sunAdded = 0;

	checkZombieSpawn(time);
	checkSunSpawn(time);

	grid.updateAnimation(time);
	//bar.updateAnimation(time);

	//update plants
	for (std::vector<Plant*>::iterator it = plants.begin(); it != plants.end(); ++it) {
		(*it)->updateAnimation(time);
		if ((*it)->checkShoot(time) == true) {//check if each plant is shooting on the current frame
			if ((*it)->getType() == Plant::PEASHOOTER) {//peashooters will shoot bullets
				(*it)->shootingAnimation(&peashooter_shootingSprite, time);
			}
			else if ((*it)->getType() == Plant::SUNFLOWER) {//sunflowers will create sun instead of shooting
				//spawnSun((*it), time);
				createSun(25);
				(*it)->shootingAnimation(&sunflower_shineSprite, time);
			}
		}
		if ((*it)->shootBullet(time) == true) {//check if each plant should spawn a bullet after it's shooting animation has finished
			spawnBullet((*it), time);
		}
		if ((*it)->getType() == Plant::WALLNUT) {//peashooters will shoot bullets
			//(*it)->health -= 1;//for testing
			if ((*it)->health <= 300) {//check if wallnut is hurt
				(*it)->hurtAnimation(&wallnut_hurtSprite);//change sprite
			}
		}
	}

	//update bullets
	for (std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
		(*it)->updateAnimation(time);
		(*it)->move(time);//bullets move a certain distance each frame
	}

	//update zombies
	for (std::vector<Zombie*>::iterator it = zombies.begin(); it != zombies.end(); ++it) {
		(*it)->move(time);//zombies move a certain distance each frame
		(*it)->updateAnimation(time);
		//(*it)->health -= 1;//for testing
		if ((*it)->health <= 200) {//check if zombie is hurt
			(*it)->hurtAnimation(&zombie_hurtSprite);//change sprite
		}
		//for testing eating animation
		/*if ((*it)->getPosition().X <= 25) {//this should be if it's colliding with a plant
			(*it)->eatingAnimation(&zombie_eatingSprite, &zombie_hurt_eatingSprite, time);
		}
		else {
			(*it)->resetData();
		}*/
		if ((*it)->health <= 0) {
			(*it)->deathAnimation(&zombie_dyingSprite, time);
		}
	}

	//update lawnmowers
	for (std::vector<Mower*>::iterator it = mowers.begin(); it != mowers.end(); ++it) {
		(*it)->move(time);
		(*it)->updateAnimation(time);
	}


	//COLLISION DETECTION
	//deleting bullets
	for (int i = 0; i<bullets.size(); i++) {
		if (bullets[i]->hitEdge() == true)
		{
			delete bullets[i];//deallocating memory
			bullets.erase(bullets.begin() + i);//removing it from the vector
			i--;
		}
	}
	//deleting lawnmowers
	for (int i = 0; i < mowers.size(); i++) {
		if (mowers[i]->hitEdge() == true)
		{
			delete mowers[i];//deallocating memory
			mowers.erase(mowers.begin() + i);//removing it from the vector
			i--;
		}
	}
	//deleting zombies
	for (int i = 0; i < zombies.size(); i++) {
		if (zombies[i]->endCollision() == true || zombies[i]->killZombie(time) == true)
		{
			delete zombies[i];//deallocating memory
			zombies.erase(zombies.begin() + i);//removing it from the vector
			i--;
		}
		//*this is broken right now*
		/*if (zombies[i]->getPosition().Y == bullets[i]->getPosition().Y)//*There may not be the same number of zombies and bullets, use another nested loop to go through all the bullets*
		{
		zombies[i]->health -= 20;
		}*/
	}

	/*for (int i = 0; i < suns.size(); i++)//update suns, unused for now
	{
		suns[i]->updateAnimation(time);
		if (suns[i]->updateLife(time)== false)
		{
			suns.erase(suns.begin() + i);
			i--;
		}
	}*/

	if (sunAdded > 0) {
		displaySunAddedTime = time;
		displaySunAdded += sunAdded;
	}
}

/*void GameHandler::collisions(Zombie zombie) {//**make this a function member of Sprite, a general checkCollision function: sprite1.checkCollision(sprite2);**
//if zombie collides with plant
if (zombie.endCollision()) {

}// If Zombie collides with end, found in Zombie.cpp and Zombie.h
//if zombie collides with bullet
Bullet hitEdge(); //if bullet collides with end of map found in Bullet.h and Bullet.cpp
}*/

void GameHandler::checkPlantBuy() {
}


//SPAWING OBJECTS
void GameHandler::placePlant(COORD pos, Plant::plantType type, int time) {
	Plant* plant = 0;
	if (type == Plant::PEASHOOTER) {
		plant = new Peashooter(&peashooterSprite, time);//creates a new peashooter
	}
	else if (type == Plant::SUNFLOWER) {
		plant = new Sunflower(&sunflowerSprite, time);//creates a new sunflower
	}
	else if (type == Plant::WALLNUT) {
		plant = new Wallnut(&wallnutSprite, time);//creates a new wallnut
	}
	plant->setPosition(pos);

	plants.push_back(plant);//adds newly created plant to the list
}

void GameHandler::spawnBullet(Plant* shooter, int time) {
	COORD spawnPos = shooter->getPosition();
	spawnPos.X += 6;
	spawnPos.Y += 1;

	Bullet* bullet = new Bullet(&bulletSprite, time);//creates a new bullet
	bullet->setPosition(spawnPos);

	bullets.push_back(bullet);//adds newly created bullet to the list
}

void GameHandler::spawnZombie(int time) {
	COORD gridPos = grid.getPosition();
	gridPos.Y += 1;
	COORD spawnPos;
	spawnPos.X = gridPos.X + grid.getSize().X + 13;
	spawnPos.Y = gridPos.Y + randNum(0, 5) * 6;

	Zombie* zombie = new Zombie(&zombieSprite, time);//creates a new zombie
	zombie->setPosition(spawnPos);

	zombies.push_back(zombie);//adds newly created zombie to the list
}

/*void GameHandler::spawnSun(Plant* flower, int time) {
COORD spawnPos = flower->getPosition();
//spawnPos.X += 1;
//spawnPos.Y -= 1;

Sun* sun = new Sun(&sunSprite, time);//creates a new sun
sun->setPosition(spawnPos);

suns.push_back(sun);//adds newly created sun to the list
createSun();
}*/

void GameHandler::createSun(int num) {//adds sun to the player's sun count
	sunCount += num;
	sunAdded += num;
}


//CHECKING SPAWN TIMERS
void GameHandler::checkZombieSpawn(int time) {
	if (time - previousZombieTime >= zombieInterval) {
		spawnZombie(time);
		previousZombieTime = time;
	}
}

void GameHandler::checkSunSpawn(int time) {
	if (time - previousSunTime >= sunInterval) {
		createSun(50);
		previousSunTime = time;
	}
}


//OTHER FUNCTIONS
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

void GameHandler::printString(HANDLE buffer, string string, COORD position, int colour) {

	CHAR_INFO* stringData = new CHAR_INFO[string.size()];
	SMALL_RECT stringPosition = { position.X, position.Y, position.X + string.size(), position.Y };
	COORD stringSize = { string.size(), 1 };

	for (int i = 0; i < string.size(); i++) {
		stringData[i].Char.AsciiChar = string[i];
		stringData[i].Attributes = colour;
	}
	WriteConsoleOutput(buffer, stringData, stringSize, { 0 , 0 }, &stringPosition);
}

void GameHandler::fullscreen()
{
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
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
	barSprite = getSprite("assets/bar.txt");
	bulletSprite = getSprite("assets/bullet.txt");
	gridSprite = getSprite("assets/lawn.txt");
	lawnmowerSprite = getSprite("assets/lawnmower.txt");
	peashooterSprite = getSprite("assets/peashooter.txt");
	peashooter_shootingSprite = getSprite("assets/peashooter_shooting.txt");
	selectionsquareSprite = getSprite("assets/selectionsquare.txt");
	sunflowerSprite = getSprite("assets/sunflower.txt");
	sunflower_shineSprite = getSprite("assets/sunflower_shine.txt");
	//sunSprite = getSprite("assets/sun.txt");
	wallnutSprite = getSprite("assets/wallnut.txt");
	wallnut_hurtSprite = getSprite("assets/wallnut_hurt.txt");
	zombieSprite = getSprite("assets/zombie.txt");
	zombie_dyingSprite = getSprite("assets/zombie_dying.txt");
	zombie_eatingSprite = getSprite("assets/zombie_eating.txt");
	zombie_hurtSprite = getSprite("assets/zombie_hurt.txt");
	zombie_hurt_eatingSprite = getSprite("assets/zombie_hurt_eating.txt");
}
