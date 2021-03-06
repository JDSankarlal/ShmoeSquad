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
#define blue_black 0x0009

GameHandler::GameHandler()
{
}
GameHandler::~GameHandler()
{
}
//INITIALIZING OBJECTS
void GameHandler::initialize(int time) {
	pauseTime = 0;//reseting pause time
	startTime = time;
	surviveTime = 0.0f;

	//clearing object lists
	deleteZombies();
	deletePlants();
	deleteBullets();
	deleteMowers();
	//deleteSuns();

	if (mode == EASY) {
		//initializing variables for spawn timers
		zombieInterval = 36000;
		zombieIncreaseInterval = 23000;
		zombieIncreaseAmount = 0.925;
		numSpawnIncreaseInterval = 90000;
		numSpawn = 1;
		numIncreaseDelay = 40000;
		
		previousZombieTime = time;
		previousSunTime = time;
		previousZombieTime = time - zombieInterval + 18000;//will spawn one zombie 18 seconds after start
		previousIncreaseTime = -1;
		previousNumSpawnIncrease = -1;

		pylonSpawnRate = 6;
		pylonSpawnIncrementor = pylonSpawnRate;
		spawnFirstPylon = false;
		startSpawningPylons = time + 80000;
	}
	else if (mode == INTENSE) {
		//initializing variables for spawn timers
		zombieInterval = 27000;
		zombieIncreaseInterval = 22000;
		zombieIncreaseAmount = 0.925;
		numSpawnIncreaseInterval = 85000;
		numSpawn = 1;
		numIncreaseDelay = 0;

		previousZombieTime = time;
		previousSunTime = time;
		previousZombieTime = time - zombieInterval + 14000;//will spawn one zombie 14 seconds after start
		previousIncreaseTime = -1;
		previousNumSpawnIncrease = -1;

		pylonSpawnRate = 5;
		pylonSpawnIncrementor = pylonSpawnRate;
		spawnFirstPylon = false;
		startSpawningPylons = time + 50000;
	}

	sunCount = 50;
	displaySunAdded = 0;

	sunflowerCooldown = 0;
	peashooterCooldown = 0;
	wallnutCooldown = 0;
	shovel = false;

	currentSunflowerCooldown = 0;
	currentPeashooterCooldown = 0;
	currentWallnutCooldown = 0;

	boxMoveTime = -1;

	//setting ascii data for grid/lawn
	grid.setData(&gridSprite);
	grid.setPosition({ 13,13 });
	int* sequence = new int[4]{ 0,1,2,1 };
	grid.setAnimation(sequence, 4, 1000, time);

	sequence = NULL;//remove dangling pointer

	//setting ascii data for selection square
	square.setData(&selectionsquareSprite);
	square.setDefaultColour(blue_black);
	square.setPosition({ 13,13 });

	//square shown in bar
	squareBar.setData(&selectionsquarebarSprite);
	squareBar.setDefaultColour(blue_black);
	squareBar.setPosition({ 13, 0 });

	//shovel
	shovelDisplay.setData(&shovelSprite);
	shovelDisplay.setDefaultColour(white_black);
	shovelDisplay.setPosition({ 51 ,3 });

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
	pos.Y += 3;
	for (SHORT i = 0; i < numChosenPlants; i++) {//placing plants inside of the bar
		chosenPlants[i]->setPosition({ pos.X + i * 12, pos.Y });
		chosenPlants[i]->setDefaultColour(white_black);
	}

	//setting up lawnmowers
	pos = grid.getPosition();
	pos.X -= 12;
	pos.Y += 2;
	for (int i = 0; i < 5; i++) {
		Mower* lawnmower = new Mower(&lawnmowerSprite, time);
		lawnmower->setPosition(pos);
		//lawnmower->activate(time);//for testing
		mowers.push_back(lawnmower);
		pos.Y += 6;
		lawnmower = NULL;
	}

	//placing plants for testing purposes
	/*pos = grid.getPosition();
	placePlant({ pos.X + 2, pos.Y + 1 }, Plant::SUNFLOWER, time);
	pos.X += 12;
	placePlant({ pos.X + 2, pos.Y + 1 }, Plant::PEASHOOTER, time);
	pos.X -= 12;
	pos.Y += 6;
	placePlant({ pos.X + 2, pos.Y + 1 }, Plant::PEASHOOTER, time);
	pos.Y += 6;
	pos.X += 60;
	placePlant({ pos.X + 2, pos.Y + 1 }, Plant::WALLNUT, time);
	pos.Y += 6;
	placePlant({ pos.X + 2, pos.Y + 1 }, Plant::WALLNUT, time);
	pos.Y -= 6;
	pos.X -= 48;
	//placePlant({ pos.X + 2, pos.Y + 1 }, Plant::PEASHOOTER, time);
	pos.Y += 6;
	//placePlant({ pos.X + 2, pos.Y + 1 }, Plant::PEASHOOTER, time);
	pos.Y += 6;
	placePlant({ pos.X + 2, pos.Y + 1 }, Plant::PEASHOOTER, time);*/
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
	
}

void GameHandler::printDisplay(HANDLE buffer)
{
	printBar(buffer);
	grid.draw(buffer);
	if (isPlacingPlant == true) {
		square.draw(buffer);
		squareBar.draw(buffer);
		if (shovel == false) {
			selectedPlant->setDefaultColour(blue_black);
			selectedPlant->setPosition({ square.getPosition().X + 2, square.getPosition().Y + 1 });
			selectedPlant->draw(buffer);
		}
	}
	for (SHORT i = 0; i < numChosenPlants; i++) {//drawing plants inside of the bar
		chosenPlants[i]->draw(buffer);
	}
	shovelDisplay.draw(buffer);
	//printing plant bar info
	COORD pos = bar.getPosition();
	pos.X += 8;
	pos.Y += 1;
	for (SHORT i = 0; i < numChosenPlants; i++) {
		//printing number
		printString(buffer, "[" + std::to_string(i + 1) + "]", { pos.X - 7 + i * 12, pos.Y }, white_black);
		//printing costs
		printString(buffer, std::to_string(chosenPlants[i]->cost), { pos.X + i * 12, pos.Y }, yellow_black);
	}
	printString(buffer, "[4]", { pos.X - 7 + 3 * 12, pos.Y }, white_black);
	//print plant cooldowns
	pos.X -= 5;
	if (currentSunflowerCooldown >= 0) {
		printString(buffer, "WAIT: " + std::to_string(currentSunflowerCooldown / 1000 + 1) + "s", { pos.X , pos.Y + 7 }, purple_black);
	}
	if (currentPeashooterCooldown >= 0) {
		printString(buffer, "WAIT: " + std::to_string(currentPeashooterCooldown / 1000 + 1) + "s", { pos.X + 12, pos.Y + 7 }, purple_black);
	}
	if (currentWallnutCooldown >= 0) {
		printString(buffer, "WAIT: " + std::to_string(currentWallnutCooldown / 1000 + 1) + "s", { pos.X + 24, pos.Y + 7 }, purple_black);
	}

	//displays the player's sun count
	pos = grid.getPosition();
	pos.Y -= 2;

	string numSun = "Sun: " + std::to_string(sunCount);

	printString(buffer, numSun, pos, yellow_black);

	if (displaySunAdded > 0) {
		string sunObtained = " + " + std::to_string(displaySunAdded);
		printString(buffer, sunObtained, { pos.X + static_cast<SHORT>(numSun.size()), pos.Y }, white_black);
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
	time -= pauseTime;//compenssatng for time game was paused on the last frame

	if (time - displaySunAddedTime >= displaySunAddedLength) {
		displaySunAdded = 0;
	}
	sunAdded = 0;
	//calculating plant cooldowns
	currentSunflowerCooldown = (sunflowerCooldown - time);
	if (currentSunflowerCooldown < 0) {
		currentSunflowerCooldown = -1;
	}
	currentPeashooterCooldown = (peashooterCooldown - time);
	if (currentPeashooterCooldown < 0) {
		currentPeashooterCooldown = -1;
	}
	currentWallnutCooldown = (wallnutCooldown - time);
	if (currentWallnutCooldown < 0) {
		currentWallnutCooldown = -1;
	}

	checkZombieSpawn(time);
	checkSunSpawn(time);

	grid.updateAnimation(time);
	//bar.updateAnimation(time);

	checkPlantBuy(time);
	placingPlant(time);

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
			if ((*it)->health <= 25) {//check if wallnut is below 1/2 health
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
		if ((*it)->getType() == Zombie::NORMAL) {
			if ((*it)->health <= (*it)->halfHP) {//check if zombie is below 1/2 health
					(*it)->hurtAnimation(&zombie_hurtSprite);//change sprite
			}
		}
		else if ((*it)->getType() == Zombie::PYLON) {
			if ((*it)->health <= (*it)->halfHP) {//check if zombie is below 1/2 health
					(*it)->hurtAnimation(&zombiepylon_hurtSprite);//change sprite
			}
		}
		if ((*it)->health <= 0) {
			if ((*it)->getType() == Zombie::NORMAL) {
				(*it)->deathAnimation(&zombie_dyingSprite, time);
			}
			else if ((*it)->getType() == Zombie::PYLON) {
				(*it)->deathAnimation(&zombiepylon_dyingSprite, time);
			}
		}
	}

	//update lawnmowers
	for (std::vector<Mower*>::iterator it = mowers.begin(); it != mowers.end(); ++it) {
		(*it)->move(time);
		(*it)->updateAnimation(time);
	}


	//COLLISION DETECTION
	//Zombie collisions
	for (int i = 0; i < zombies.size(); i++) {
		if (zombies[i]->endCollision() == true) {
			surviveTime = (static_cast<float>(time) - static_cast<float>(startTime)) / 1000.0f;
			gameFinished();
		}
		//collisions with bullets
		for (int j = 0; j < bullets.size(); j++)
		{
			if (zombies[i]->checkCollision(bullets[j]) == true) {
				zombies[i]->takeDamage(2, time); //reduce zombies health by 2
				bullets[j]->hit();//set bullet to be dead
			}
		}
		if (zombies[i]->getState() != Zombie::DEAD) {//zombies don't collide with this if they're dead, except bullets
			//collisions with lawnmowers
			for (int j = 0; j < mowers.size(); j++)
			{
				if (zombies[i]->checkCollision(mowers[j]) == true) {
					mowers[j]->activate(time);//activate lawnmower if touched by zombie
					zombies[i]->health = 0; //instantly kill zombie
					break;
				}
			}
			//collisions with plants
			bool isTouchingPlant = false;
			for (int j = 0; j < plants.size(); j++)
			{
				if (zombies[i]->checkCollision(plants[j]) == true) {
					if (zombies[i]->getType() == Zombie::NORMAL) {
						zombies[i]->eatingAnimation(&zombie_eatingSprite, &zombie_hurt_eatingSprite, time);
					}
					else if (zombies[i]->getType() == Zombie::PYLON) {
						zombies[i]->eatingAnimation(&zombiepylon_eatingSprite, &zombiepylon_hurt_eatingSprite, time);
					}
					plants[j]->takeDamage(zombies[i]->dealDamage(time), time);
					isTouchingPlant = true;
					break;
				}
			}
			if (isTouchingPlant == false && zombies[i]->isEating == true) {
				zombies[i]->isEating = false;
				zombies[i]->resetData();
			}
		}
	}
	//deleting zombies
	for (int i = 0; i < zombies.size(); i++) {
		if (zombies[i]->endCollision() == true || zombies[i]->killZombie(time) == true)
		{
			delete zombies[i];//deallocating memory4
			zombies[i] = NULL;
			zombies.erase(zombies.begin() + i);//removing it from the vector
			i--;
		}
	}
	//deleting lawnmowers
	for (int i = 0; i < mowers.size(); i++) {
		if (mowers[i]->hitEdge() == true)
		{
			delete mowers[i];//deallocating memory
			mowers[i] = NULL;
			mowers.erase(mowers.begin() + i);//removing it from the vector
			i--;
			continue;
		}
		for (int j = 0; j < plants.size(); j++)
		{//kill plants if they collide with a lawnmower
			if (mowers[i]->checkCollision(plants[j]) == true) {
				plants[j]->health = 0;
			}
		}
	}
	//deleting plants
	for (int i = 0; i < plants.size(); i++) {
		if (plants[i]->health <= 0)
		{
			delete plants[i];//deallocating memory
			plants[i] = NULL;
			plants.erase(plants.begin() + i);//removing it from the vector
			i--;
		}
	}
	//deleting bullets
	for (int i = 0; i<bullets.size(); i++) {
		if (bullets[i]->hitEdge() == true || bullets[i]->isAlive == false)
		{
			delete bullets[i];//deallocating memory
			bullets[i] = NULL;
			bullets.erase(bullets.begin() + i);//removing it from the vector
			i--;
		}
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

	checkPause();
}

void GameHandler::checkPlantBuy(int time) {
		if (Events::keyDown(Events::One)) {
			if (selectedPlant != NULL) {
				delete selectedPlant;
				selectedPlant = NULL;
			}
			selectedPlant = new Sunflower(&sunflowerSprite, time);
			squareBar.setPosition({ chosenPlants[0]->getPosition().X - 2, chosenPlants[0]->getPosition().Y - 3 });
			if (sunCount >= selectedPlant->cost && time >= sunflowerCooldown)
			{
				isPlacingPlant = true;
				selectedPlant->setData(&sunflowerSprite);
			}
			else {
				isPlacingPlant = false;
			}
			shovel = false;
		}
		else if (Events::keyDown(Events::Two)) {
			if (selectedPlant != NULL) {
				delete selectedPlant;
				selectedPlant = NULL;
			}
			selectedPlant = new Peashooter(&peashooterSprite, time);
			squareBar.setPosition({ chosenPlants[1]->getPosition().X - 2, chosenPlants[1]->getPosition().Y - 3 });
			if (sunCount >= selectedPlant->cost && time >= peashooterCooldown)
			{
				isPlacingPlant = true;
				selectedPlant->setData(&peashooterSprite);
			}
			else {
				isPlacingPlant = false;
			}
			shovel = false;
		}
		else if (Events::keyDown(Events::Three)) {
			if (selectedPlant != NULL) {
				delete selectedPlant;
				selectedPlant = NULL;
			}
			selectedPlant = new Wallnut(&wallnutSprite, time);
			squareBar.setPosition({ chosenPlants[2]->getPosition().X - 2, chosenPlants[2]->getPosition().Y - 3 });
			if (sunCount >= selectedPlant->cost && time >= wallnutCooldown)
			{
				isPlacingPlant = true;
				selectedPlant->setData(&wallnutSprite);
			}
			else {
				isPlacingPlant = false;
			}
			shovel = false;
		}
		else if (Events::keyDown(Events::Four))
		{
			if (selectedPlant != NULL) {
				delete selectedPlant;
				selectedPlant = NULL;
			}
			squareBar.setPosition({ chosenPlants[2]->getPosition().X + 10, chosenPlants[2]->getPosition().Y - 3 });
			shovel = true;
			isPlacingPlant = true;
		}
		
}

// The following fucntion makes the box move and not be able to go outside of the grid
void GameHandler::placingPlant(int time) {
	
	if (isPlacingPlant == true)
	{
		if (boxMoveTime > 0 && time - boxMoveTime >= boxMoveInterval || boxMoveTime < 0)
		{
			if (Events::keyDown(Events::Up))
			{
				boxMoveTime = time;
				if (square.getPosition().Y > grid.getPosition().Y)
				{
					square.setPosition({ square.getPosition().X,  square.getPosition().Y - 6 });
				}
			}
			else if (Events::keyDown(Events::Down))
			{
				boxMoveTime = time;
				if (square.getPosition().Y + square.getSize().Y < grid.getPosition().Y + grid.getSize().Y)
				{
					square.setPosition({ square.getPosition().X, square.getPosition().Y + 6 });
				}
			}
			else if (Events::keyDown(Events::Left))
			{
				boxMoveTime = time;
				if (square.getPosition().X > grid.getPosition().X)
				{
					square.setPosition({ square.getPosition().X - 12, square.getPosition().Y });
				}
			}
			else if (Events::keyDown(Events::Right))
			{
				boxMoveTime = time;
				if (square.getPosition().X + square.getSize().X < grid.getPosition().X + grid.getSize().X)
				{
					square.setPosition({ square.getPosition().X + 12, square.getPosition().Y });
					
				}
			}
		}
		if (Events::keyDown(Events::Space))
		{
			const COORD position = { square.getPosition().X + 2, square.getPosition().Y + 1 };
			bool canPlacePlant = true;
			for (int i = 0; i < plants.size(); i++) {
				if (plants[i]->getPosition().X == position.X && plants[i]->getPosition().Y == position.Y)
				{
					if (shovel == true)
					{
						delete plants[i];
						plants.erase(plants.begin() + i);
						shovel = false;
						isPlacingPlant = false;
					}
					canPlacePlant = false;
					break;
				}
				else {
					if (shovel == false) {
						canPlacePlant = true;
					}
					else {
						canPlacePlant = false;
					}
				}
			}
			if (canPlacePlant == true && shovel == false )
			{
				placePlant(position, selectedPlant->getType(), time);
				isPlacingPlant = false;
				sunCount -= selectedPlant->cost;
				if (selectedPlant->getType() == Plant::SUNFLOWER)
				{
					sunflowerCooldown = time + selectedPlant->cooldown;
				}
				else if (selectedPlant->getType() == Plant::PEASHOOTER)
				{
					peashooterCooldown = time + selectedPlant->cooldown;
				}
				else if (selectedPlant->getType() == Plant::WALLNUT)
				{
					wallnutCooldown = time + selectedPlant->cooldown;
				}
				if (selectedPlant != NULL) {
					delete selectedPlant;
					selectedPlant = NULL;
				}
			}
			boxMoveTime = -1;
		}
	}
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
	int rowNum;
	bool match;
	while (true) {
		rowNum = randNum(0, 5);
		for (int i = 0; i < 3; i++) {
			if (rowNum == previousRows[i]) {//match found
				match = true;
				break;//stop as soon as 1 match is found, generate a new number
			}
			else {//no match
				match = false;
			}
		}
		if (match == false) {//if random number doesn't match any of the last 4 generated
			previousRows[incrementor] = rowNum;
			incrementor++;
			if (incrementor >= 3) {//reset incrementor to 0
				incrementor = 0;
			}
			break;
		}
	}
	COORD gridPos = grid.getPosition();
	gridPos.Y += 1;
	COORD spawnPos;
	spawnPos.X = gridPos.X + grid.getSize().X + 13;
	spawnPos.Y = gridPos.Y + rowNum * 6;

	Zombie* zombie;
	if (time >= startSpawningPylons) {
		if (pylonSpawnIncrementor % pylonSpawnRate == 0) {
			zombie = new PylonZombie(&zombiepylonSprite, time);//creates a new pylon zombie
			spawnFirstPylon = true;
		}
		else {
			zombie = new Zombie(&zombieSprite, time);//creates a new zombie
		}
	}
	else {
		zombie = new Zombie(&zombieSprite, time);//creates a new zombie
	}
	zombie->setPosition(spawnPos);

	zombies.push_back(zombie);//adds newly created zombie to the list

	if (spawnFirstPylon == true) {
		pylonSpawnIncrementor++;
	}
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
		for (int i = 0; i < numSpawn; i++) {
			spawnZombie(time);
		}
		previousZombieTime = time;
	}
	//increase zombie spawn rate
	if (previousIncreaseTime < 0) {
		previousIncreaseTime = time;
	}
	if (time - previousIncreaseTime >= zombieIncreaseInterval) {
		zombieInterval *= zombieIncreaseAmount;//spawn interval decreased by 20% every 35 seconds
		previousIncreaseTime = time;
	}
	if (previousNumSpawnIncrease < 0) {
		previousNumSpawnIncrease = time + numIncreaseDelay;// -numSpawnIncreaseInterval + 60000;//increase to two zombies after 60 seconds
	}
	if (time - previousNumSpawnIncrease >= numSpawnIncreaseInterval) {
		previousNumSpawnIncrease = time;
		numSpawn++;
		if (numSpawn >= 5) {
			numSpawn = 5;
		}
		if (spawnFirstPylon == true) {
			pylonSpawnRate -= 1;
			if (pylonSpawnRate <= 3) {
				pylonSpawnRate = 3;
			}
		}
	}
}

void GameHandler::checkSunSpawn(int time) {
	if (time - previousSunTime >= sunInterval) {
		createSun(25);
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

void GameHandler::mainMenu()
{
	lose = false;
	runProgram = true;
	menuMain.setData(&menu_Main);
	menuMain.setPosition({ 13,3 });
	cls(GetStdHandle(STD_OUTPUT_HANDLE), white_black);
	menuMain.draw(GetStdHandle(STD_OUTPUT_HANDLE));
	while (true) {
		if (Events::keyDown(Events::E)) {
			mode = EASY;
			break;
		}
		else if (Events::keyDown(Events::I)) {
			mode = INTENSE;
			break;
		}
		else if (Events::keyDown(Events::H)) {
			howToPlay();
			cls(GetStdHandle(STD_OUTPUT_HANDLE), white_black);
			menuMain.draw(GetStdHandle(STD_OUTPUT_HANDLE));
		}
		else if (Events::keyDown(Events::C)) {
			creditsDisplay();
			cls(GetStdHandle(STD_OUTPUT_HANDLE), white_black);
			menuMain.draw(GetStdHandle(STD_OUTPUT_HANDLE));
		}
		else if (Events::keyDown(Events::Q)) {
			lose = true;
			exitGame();
			break;
		}
		Sleep(10);
	}
}

void GameHandler::gameFinished()
{
	lose = true;
	gameOver.setData(&game_Over);
	gameOver.setPosition({ 0,3 });
	cls(GetStdHandle(STD_OUTPUT_HANDLE), white_black);
	gameOver.draw(GetStdHandle(STD_OUTPUT_HANDLE));
	std::stringstream stream;
	stream << std::fixed << std::setprecision(3) << surviveTime;
	std::string string = stream.str();
	if (mode == EASY) {
		printString(GetStdHandle(STD_OUTPUT_HANDLE), "You Survived For: " + string + "s in Easy Mode", { 0,0 }, yellow_black);
	}
	else if (mode == INTENSE) {
		printString(GetStdHandle(STD_OUTPUT_HANDLE), "You Survived For: " + string + "s in Intense Mode", { 0,0 }, yellow_black);
	}
	while (true) {
		if (Events::keyDown(Events::R)) {
			break;
		}
		else if (Events::keyDown(Events::Q)) {
			exitGame();
			break;
		}
		Sleep(10);
	}
}

void GameHandler::howToPlay()
{
	howPlay.setData(&how_Play);
	howPlay.setPosition({ 13,3 });
	cls(GetStdHandle(STD_OUTPUT_HANDLE), white_black);
	howPlay.draw(GetStdHandle(STD_OUTPUT_HANDLE));
	while (true) {
		if (Events::keyDown(Events::B)) {
			break;
		}
		Sleep(10);
	}
}

void GameHandler::creditsDisplay()
{
	credits.setData(&creditsSprite);
	credits.setPosition({ 0,0 });
	cls(GetStdHandle(STD_OUTPUT_HANDLE), white_black);
	credits.draw(GetStdHandle(STD_OUTPUT_HANDLE));
	while (true) {
		if (Events::keyDown(Events::B)) {
			break;
		}
		Sleep(10);
	}
}

void GameHandler::exitGame() {
	for (int i = 0; i < numChosenPlants; i++) {
		if (chosenPlants[i] != NULL) {
			delete chosenPlants[i];
			chosenPlants[i] = NULL;
		}
	}
	if (chosenPlants != NULL) {
		delete[] chosenPlants;
		chosenPlants = NULL;
	}
	if (selectedPlant != NULL) {
		delete selectedPlant;
		selectedPlant = NULL;
	}
	deleteZombies();
	deletePlants();
	deleteBullets();
	deleteMowers();
	runProgram = false;
}

void GameHandler::checkPause() {
	int startPauseTime = clock() / (double)CLOCKS_PER_SEC * 1000;//getting current time;
	int endPauseTime = 0;
	if (Events::keyDown(Events::Escape)) {
		pauseScreen.setData(&pauseSprite);
		pauseScreen.setPosition({ 67 - pauseScreen.getSize().X / 2, 25 - pauseScreen.getSize().Y / 2 });
		pauseScreen.draw(GetStdHandle(STD_OUTPUT_HANDLE));
		while (true) {
			if (Events::keyDown(Events::R)) {
				endPauseTime = clock() / (double)CLOCKS_PER_SEC * 1000;//getting current time
				pauseTime += (endPauseTime - startPauseTime);//time game was paused for
				break;
			}
			else if (Events::keyDown(Events::M)) {
				lose = true;
				break;
			}
			Sleep(10);
		}
	}
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
	selectionsquarebarSprite = getSprite("assets/selectionsquarebar.txt");
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
	zombiepylonSprite = getSprite("assets/zombiepylon.txt");
	zombiepylon_dyingSprite = getSprite("assets/zombiepylon_dying.txt");
	zombiepylon_eatingSprite = getSprite("assets/zombiepylon_eating.txt");
	zombiepylon_hurtSprite = getSprite("assets/zombiepylon_hurt.txt");
	zombiepylon_hurt_eatingSprite = getSprite("assets/zombiepylon_hurt_eating.txt");
	menu_Main = getSprite("assets/Main_Menu.txt");
	game_Over = getSprite("assets/Game_Over.txt");
	how_Play = getSprite("assets/howToPlay.txt");
	shovelSprite = getSprite("assets/shovel.txt");
	pauseSprite = getSprite("assets/pause.txt");
	creditsSprite = getSprite("assets/credits.txt");
}
