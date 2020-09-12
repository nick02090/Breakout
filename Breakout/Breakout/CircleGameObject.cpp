#include "CircleGameObject.h"

CircleGameObject::CircleGameObject(SDL_Renderer* _renderer) : GameObject(_renderer, GameObjectType::Circle)
{
	// Initialize member variables
	radius = 0.f;
}

void CircleGameObject::render(float _widthFactor, float _heightFactor)
{
	// Update scale factors
	widthFactor = _widthFactor;
	heightFactor = _heightFactor;

	// Create a rect to position the texture
	SDL_FRect rect;
	rect.x = screenPosition.x;
	rect.y = screenPosition.y;
	rect.w = 2 * radius / widthFactor;
	rect.h = 2 * radius / heightFactor;

	// Render the texture on the screen
	SDL_RenderCopyF(renderer, texture, NULL, &rect);
}

float CircleGameObject::getRadius()
{
	return radius;
}
