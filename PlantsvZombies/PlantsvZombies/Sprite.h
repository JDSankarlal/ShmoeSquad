#pragma once 
#include <Windows.h>
#include <cstdio>
#define numColumns 3
#define numRows 5

class Sprite {
public:
	Sprite() {}
	~Sprite() {}

	Sprite* init(const char data[numRows][numColumns]) {
		for (unsigned int i = 0; i < numRows; i++) {
			for (unsigned int j = 0; j < numColumns; j++) {
				ascii[i][j] = data[i][j];
			}
		}
		return this;
	}

	Sprite* init(char data) {
		for (unsigned int i = 0; i < numRows; i++) {
			for (unsigned int j = 0; j < numColumns; j++) {
				ascii[i][j] = data;
			}
		}
		return this;
	}

	Sprite* setPosition(const COORD &pos) {
		position = pos;
		return this;
	}

	const COORD& getPosition() {
		return position;
	}

	Sprite* draw() {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		for (SHORT i = 0; i < numRows; i++) {
			for (SHORT j = 0; j < numColumns; j++) {
				printf("%c", ascii[i][j]);
			}
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ position.X, position.Y + i });
		}
		return this;
	}

private:
	COORD position;
	char ascii[numRows][numColumns];
};