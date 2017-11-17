#pragma once
#include "Sprite.h"

class Zombie : public Sprite
{
public:
	Zombie();
	
	~Zombie();

	char spriteData[5][7] = {//sets ASCII data for what a zombie looks like
		{ '0','0','0','0','0','0','0' },
		{ '0','0','0','0','0','0','0' },
		{ '0','0','0','0','0','0','0' },
		{ '0','0','0','0','0','0','0' },
		{ '0','0','0','0','0','0','0' }
	};
};

