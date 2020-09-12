#include "Ball.h"

Ball::Ball(SDL_Renderer* _renderer) : CircleGameObject(_renderer)
{
	// Set initial previous wall hit
	previousWallHit = WallHit::Default;
	// Set the radius
	radius = Radius;
	// Load the balls texture
	texture = util::loadTexture(renderer, TexturePath);
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