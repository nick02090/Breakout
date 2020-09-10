#include "Ball.h"

Ball::Ball(SDL_Renderer* _renderer) : GameObject(_renderer)
{
	// Set object type
	type = GameObjectType::Circle;
	// Load all necessary assets
	texture = util::loadTexture(renderer, TexturePath);
	// Set initial previous wall hit
	previousWallHit = WallHit::Default;
	// Set ball size parameters
	width = Width;
	height = Height;
	radius = 10.f;
}

Ball::~Ball()
{
	// Free loaded images
	SDL_DestroyTexture(texture);
	texture = NULL;
}

void Ball::render(util::Position _screenPosition, float widthFactor, float heightFactor)
{
	// Update position on the screen
	screenPosition = _screenPosition;

	// Create a rect to position the texture
	SDL_FRect rect;
	rect.x = screenPosition.x;
	rect.y = screenPosition.y;
	rect.w = width / widthFactor;
	rect.h = height / heightFactor;

	// Render the texture on the screen
	SDL_RenderCopyF(renderer, texture, NULL, &rect);
}

bool Ball::hasHitWall()
{
	// Ball has hit bottom or upper screen bound (wall)
	if (screenPosition.x == 0.f || screenPosition.x == 1024.f - 20.f)
	{
		previousWallHit = WallHit::Horizontal;
		return true;
	}
	// Ball has hit left or right screen bound (wall)
	if (screenPosition.y == 0.f)
	{
		previousWallHit = WallHit::Vertical;
		return true;
	}
	// Ball didn't hit the wall
	return false;
}

Ball::WallHit Ball::getPreviousWallHit()
{
	return previousWallHit;
}

bool Ball::hasFellDown()
{
	if (screenPosition.y >= 660.f)
	{
		return true;
	}
	return false;
}

float Ball::getVelocity()
{
	return velocity;
}