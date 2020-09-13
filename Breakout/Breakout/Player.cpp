#include "Player.h"

Player::Player(SDL_Renderer* _renderer) : RectangleGameObject(_renderer)
{
	// Set member variables
	currentLives = MaxLives;
	currentScore = 0;
	width = Width;
	height = Height;
	// Load the players texture
	texture = util::loadTexture(renderer, TexturePath);
}

void Player::render(float _widthFactor, float _heightFactor)
{
	// Render the player
	RectangleGameObject::render(_widthFactor, _heightFactor);

	// Update velocity
	velocity = util::clamp(velocity - 0.15f, 0.f, MaxVelocity);
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
	velocity = 0.f;
}

void Player::turnOffAcceleration()
{
	acceleration = 0.f;
}

void Player::increaseAcceleration(bool isNegativeXAxis)
{
	// Turn off acceleration if the direction is changed
	if ((velocityMultiplier < 0 && !isNegativeXAxis) || (velocityMultiplier > 0 && isNegativeXAxis))
	{
		acceleration = 0.f;
		velocity = 0.f;
	}


	if (isNegativeXAxis)
	{
		velocityMultiplier = -1.f;
	}
	else
	{
		velocityMultiplier = 1.f;
	}
	acceleration += 0.15f;
}

float Player::getVelocity()
{
	velocity = util::clamp(velocity + acceleration, 0.f, MaxVelocity);
	return velocity * velocityMultiplier;
}