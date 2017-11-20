#pragma once 
#include <Windows.h>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
using std::ifstream;
using std::string;

class Sprite {
public:
	Sprite() {
		getData("assets/default.txt");//set sprite data to a default just incase one gets created without being given ascii data
		previousMoveTime = 0;
		moveInterval = 1000;//move every 1s
	}
	~Sprite() {}

	int numRows = 0;//width of sprite
	int numCols = 0;//height of sprite

	int moveInterval;//number of ms before sprite moves
	int previousMoveTime;//the last time the sprite moved
	COORD moveVector{ 0,0 };//Amount the sprite will move each time it moves

	void getData(string fileName) {//gets the ascii data from a text file
		ifstream file;
		file.open(fileName);
		file >> std::noskipws;//tells it not to skip white space while scanning file
		int charNum = 0;
		int line = 0;
		char c;
		numRows = 0;
		numCols = 1;
		while (file >> c) {//gets the number of rows and columns in the file to set the size of the array to store the data itn
			if (c == '\n') {
				charNum = 0;
				numCols++;
			}
			else {
				charNum++;
			}
		}
		numRows = charNum;
		ascii = new char* [numCols];//allocates memory for an array of pointers
		for (int i = 0; i < numCols; i++) {//allocates memory for each pointer in the above array to be an array of characters
			ascii[i] = new char [numRows];
		}
		charNum = 0;
		file.close();
		file.open(fileName);
		char c2;
		while (file >> c2){
			ascii[line][charNum] = c2;
			charNum++;
			if (c2 == '\n') {
				charNum = 0;
				line++;
			}
		}
		file.close();
		COORD startPos{ 0,0 };
		setPosition(startPos);
	}

	//the below function is now obselete, probably won't use it ever again
	/*void init(const char data[numRows][numColumns]) {//set what the sprite looks like
		for (unsigned int i = 0; i < numRows; i++) {
			for (unsigned int j = 0; j < numColumns; j++) {
				ascii[i][j] = data[i][j];
			}
		}
		COORD startPos{ 0,0 };
		setPosition(startPos);
	}*/

	void move(int time) {
		if (time - previousMoveTime >= moveInterval) {//shoot at set interval
			previousMoveTime = time;
			updatePosition();
		}
	}

	void setPosition(const COORD &pos) {//sets position to draw the sprite at
		position = pos;
	}

	void updatePosition() {//updates position to draw the sprite at
		position.X = position.X + moveVector.X;
		position.Y = position.Y + moveVector.Y;
	}

	const COORD& getPosition() {//used to get the position of a sprite, because position is a private variable
		return position;
	}

	void draw() {//draw sprite to screen at its current position
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		for (SHORT i = 0; i < numCols; i++) {
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ position.X, position.Y + i });
			for (SHORT j = 0; j < numRows; j++) {
				printf("%c", ascii[i][j]);
			}
		}
	}

private:
	COORD position;//the current position of a sprites Top Left corner
	char** ascii;//a double pointer, will be initialized to a 2D array to store the ascii data for the sprite
};