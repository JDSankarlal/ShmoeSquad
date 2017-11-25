#pragma once 
#include <Windows.h>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <string>
using std::ifstream;
using std::string;
using std::vector;

class Sprite {
public:
	Sprite() {
		//getData("assets/default.txt");//set sprite data to a default just incase one gets created without being given ascii data
		//previousMoveTime = 0;
		//moveInterval = 1000;//move every 1s
	}
	~Sprite() {
	}

	int moveInterval;//number of ms before sprite moves
	int previousMoveTime;//the last time the sprite moved
	COORD moveVector{ 0,0 };//Amount the sprite will move each time it moves

	void getData(string fileName)
	{//gets the ascii data from a text file
		ifstream file;
		file.open(fileName);
		file >> std::noskipws;//tells it not to skip white space while scanning file
		string s;
		while (getline(file, s)) {
			asciiData.push_back(s);//adding each line from the file into a vector of strings
		}
		file.close();
		//getting sprites width and height
		SHORT width = asciiData[0].size();
		SHORT height = asciiData.size();
		size = { width, height };
		setPosition({ 0,0 });//setting default position to 0,0
	}

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

	const COORD& getPosition() {//used to get the position of a sprite
		return position;
	}

	const COORD& getSize() {//used to get the size of a sprite
		return size;
	}
	
	void draw(HANDLE buffer, int colour)
	{//draw sprite to screen at its current position
		CHAR_INFO* spriteData = new CHAR_INFO[size.X * size.Y];
		SMALL_RECT spritePosition;
		spritePosition = { position.X, position.Y, position.X + size.X, position.Y + size.Y };

		for (SHORT i = 0; i < size.Y; i++) {
			for (SHORT j = 0; j < size.X; j++) {
				//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ position.X + j, position.Y + i });
				//printf("%c", asciiData[i][j]);
				spriteData[j + size.X * i].Char.AsciiChar = asciiData[i][j];
				spriteData[j + size.X * i].Attributes = colour;
			}
				WriteConsoleOutput(buffer, spriteData, size, { 0 , 0 }, &spritePosition);
		}
	}

private:
	COORD position;//the current position of a sprites Top Left corner
	COORD size;//the width and height of a sprite
	vector<string> asciiData;//a vector of strings, used to store sprite data
};