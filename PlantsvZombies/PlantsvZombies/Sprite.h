#pragma once 
#include <Windows.h>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
//#define numColumns 7//height of Sprites
//#define numRows 6//width of Sprites, all sprites are the same size
using std::ifstream;
using std::string;

class Sprite {
public:
	Sprite() {
		getData("assets/default.txt");
	}
	~Sprite() {}

	int numRows = 0;//width of sprite
	int numCols = 0;//height of sprite

	COORD movePosition{ 0,0 };//Amount the sprite will move

	void setPosition(const COORD &pos) {//sets position to draw the sprite at
		position = pos;
	}

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

	/*void init(const char data[numRows][numColumns]) {//set what the sprite looks like
		for (unsigned int i = 0; i < numRows; i++) {
			for (unsigned int j = 0; j < numColumns; j++) {
				ascii[i][j] = data[i][j];
			}
		}
		COORD startPos{ 0,0 };
		setPosition(startPos);
	}*/

	void updatePosition() {//updates position to draw the sprite at
		position.X = position.X + movePosition.X;
		position.Y = position.Y + movePosition.Y;
	}

	const COORD& getPosition() {
		return position;
	}

	void draw() {//draw sprite to screen
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		for (SHORT i = 0; i < numCols; i++) {
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ position.X, position.Y + i });
			for (SHORT j = 0; j < numRows; j++) {
				printf("%c", ascii[i][j]);
			}
		}
	}

private:
	COORD position;//Sprites current position
	char** ascii;
};