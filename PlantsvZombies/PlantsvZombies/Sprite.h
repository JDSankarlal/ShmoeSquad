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
		defaultAnimation();
		previousFrameTime = 0;
	}
	Sprite(vector<vector<string>>* spriteData, int time) {
		defaultData = spriteData;
		resetData();
		previousFrameTime = time;

		//previousMoveTime = time;
		//moveInterval = 1000;//move every 1s
	}
	~Sprite() {
	}

	void setAnimation(int*& sequence, int numFrames, int animationTime, int time) {//set values for animating the sprite
		frameSequence = sequence;
		totalNumFrames = numFrames;
		frameTime = animationTime;
		frameNum = 0;
		previousFrameTime = time;
	}
	
	void setData(vector<vector<string>>* spriteData)
	{//sets the ascii data for the sprite
		asciiData = *spriteData;
		//getting sprites width and height
		SHORT width = asciiData[0][0].size();
		SHORT height = asciiData[0].size();
		size = { width, height };
		//setPosition({ 0,0 });//setting default position to 0,0
	}

	void resetData() {
		setData(defaultData);
		defaultAnimation();
	}

	virtual void defaultAnimation() {
		colour = 0x000f;//white_black
		frameTime = 1000;//change animation frame every 1s
		frameSequence = new int[1]{ 0 };
		totalNumFrames = 1;
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

	void updateAnimation(int time) {
		if (time - previousFrameTime >= frameTime) {
			previousFrameTime = time;
			frameNum++;
			if (frameNum >= totalNumFrames) {
				frameNum = 0;
				if (inAnimation == true) {
					if (loopNum >= numLoops) {
						resetData();
						loopNum = 1;
						inAnimation = false;
					}
					else {
						loopNum++;
					}
				}
			}
		}
	}
	
	virtual void draw(HANDLE buffer)
	{//draw sprite to screen at its current position
		CHAR_INFO* spriteData = new CHAR_INFO[size.X * size.Y];
		SMALL_RECT spritePosition = { position.X, position.Y, position.X + size.X, position.Y + size.Y };

		for (SHORT i = 0; i < size.Y; i++) {
			for (SHORT j = 0; j < size.X; j++) {
				spriteData[j + size.X * i].Char.AsciiChar = asciiData[frameSequence[frameNum]][i][j];
				spriteData[j + size.X * i].Attributes = colour;
			}
				WriteConsoleOutput(buffer, spriteData, size, { 0 , 0 }, &spritePosition);
		}
	}

protected:
	vector<vector<string>>* defaultData = 0;//the default ascii data for a sprite
	bool inAnimation = false;//keeps track of wether the sprite is in a special animation or not
	int numLoops = 1;//number of times to loop through an animation
	int loopNum = 1;//keeps track of the number of loops of animation that have occured
	int colour = 0x0007;//the sprites current colour, default is dull white

	int* frameSequence;//array of the order the animation frames display in
	int totalNumFrames;//the number of frames of animation the sprite has
	int frameTime = 10000;//time each frame of animation is drawn for
	int previousFrameTime;//time at which the last frame of animation was changed
	int frameNum = 0;//the current frame being drawn

	int moveInterval;//number of ms inbetween sprite movements
	int previousMoveTime;//the last time the sprite moved
	COORD moveVector{ 0,0 };//Distance and direction the sprite will move each time it moves

private:
	COORD position;//the current position of a sprites Top Left corner
	COORD size;//the width and height of a sprite
	vector<vector<string>> asciiData;//a vector of strings, used to store sprite data
};