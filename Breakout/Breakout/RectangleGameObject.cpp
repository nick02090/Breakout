#include "RectangleGameObject.h"

RectangleGameObject::RectangleGameObject(SDL_Renderer* _renderer) 

	: GameObject(_renderer, GameObjectType::Rectangle)
{
	// Initialize member variables
	width = 0.f;
	height = 0.f;
}

RectangleGameObject::~RectangleGameObject()
{
}

void RectangleGameObject::render(float _widthFactor, float _heightFactor)
{
	// Update scale factors
	widthFactor = _widthFactor;
	heightFactor = _heightFactor;

	// Create a rect to position the texture
	SDL_FRect rect;
	rect.x = screenPosition.x;
	rect.y = screenPosition.y;
	rect.w = width / widthFactor;
	rect.h = height / heightFactor;

	// Render the texture on the screen
	SDL_RenderCopyF(renderer, texture, NULL, &rect);
}

float RectangleGameObject::getWidth()
{
	return width;
}

float RectangleGameObject::getHeight()
{
	return height;
}
