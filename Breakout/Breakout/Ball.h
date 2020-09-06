#pragma once
#include "GameObject.h"
class Ball : public GameObject
{
public:
	Ball(SDL_Renderer* _renderer) : GameObject(_renderer) 
	{
		type = GameObjectType::Circle;
	}
	void render(util::Position screenPosition)
	{

	}
};

