#pragma once 
#include <Windows.h>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#define numColumns 7//height of Sprites
#define numRows 6//width of Sprites, all sprites are the same size
using std::ifstream;
using std::string;

class Sprite {
public:
	Sprite() {}
	~Sprite() {}

	COORD movePosition{ 0,0 };//Amount the sprite will move

	void setPosition(const COORD &pos) {//sets position to draw the sprite at
		position = pos;
	}

	void getData(string fileName) {//gets the ascii data from a text file
		ifstream file;
		file.open(fileName);
		file >> std::noskipws;//tells it not to skip white space while scanning file
		int charNum = 0;
		int line = 1;
		char c;
		while (file >> c){
			ascii[line][charNum] = c;
			charNum++;
			if (c == '\n') {
				charNum = 0;
				line++;
			}
		}
		file.close();
		COORD startPos{ 0,0 };
		setPosition(startPos);
	}

	void init(const char data[numRows][numColumns]) {//set what the sprite looks like
		for (unsigned int i = 0; i < numRows; i++) {
			for (unsigned int j = 0; j < numColumns; j++) {
				ascii[i][j] = data[i][j];
			}
		}
		COORD startPos{ 0,0 };
		setPosition(startPos);
	}

	void updatePosition() {//updates position to draw the sprite at
		position.X = position.X + movePosition.X;
		position.Y = position.Y + movePosition.Y;
	}

	const COORD& getPosition() {
		return position;
	}

	void draw() {//draw sprite to screen
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		for (SHORT i = 0; i < numRows; i++) {
			for (SHORT j = 0; j < numColumns; j++) {
				printf("%c", ascii[i][j]);
			}
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ position.X, position.Y + i });
		}
	}

private:
	COORD position;//Sprites current position
	char ascii[numRows][numColumns];
};