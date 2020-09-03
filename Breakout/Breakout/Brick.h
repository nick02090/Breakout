#pragma once
#include "GameObject.h"
class SDL_Texture;
class Brick : public GameObject
{
private:
	char ID;
	SDL_Texture* texture;
	int hitPoints;
	//Sound* hitSound;
	//Sound* breakSound;
	int breakScore;
	char* name;
};

