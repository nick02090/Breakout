#include "Player.h"

Player::Player(SDL_Renderer* _renderer) : GameObject(_renderer, GameObjectType::Rectangle)
{
	// Load all necessary assets
	texture = util::loadTexture(renderer, TexturePath);
	// Set member variables
	currentLives = MaxLives;
	currentScore = 0;
	// Set player size
	width = Width;
	height = Height;
	// Set player size factors
	widthFactor = 1.f;
	heightFactor = 1.f;
}

Player::~Player()
{
	// Free loaded images
	SDL_DestroyTexture(texture);
	texture = NULL;
}

void Player::render(util::Position _screenPosition, float _widthFactor, float _heightFactor)
{
	// Update scale factors
	widthFactor = _widthFactor;
	heightFactor = _heightFactor;

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

	// Update velocity
	velocity = util::clamp(velocity - 1.f, MinVelocity, MaxVelocity);
}

void Player::addToScore(int value)
{
	currentScore += value;
}

int Player::getCurrentScore()
{
	return currentScore;
}

int Player::getCurrentLives()
{
	return currentLives;
}

void Player::reduceLives()
{
	currentLives -= 1;
}

bool Player::isDead()
{
	return currentLives == 0;
}

void Player::reset()
{
	currentLives = MaxLives;
	currentScore = 0;
	acceleration = 0.f;
	velocity = MinVelocity;
}

void Player::turnOffAcceleration()
{
	acceleration = 0.f;
}

void Player::increaseAcceleration(bool isNegativeXAxis)
{
	if (isNegativeXAxis)
	{
		velocityMultiplier = -1.f;
	}
	else
	{
		velocityMultiplier = 1.f;
	}
	acceleration += 1.f;
}

float Player::getVelocity()
{
	velocity = util::clamp(velocity + acceleration, MinVelocity, MaxVelocity);
	return velocity * velocityMultiplier;
}