#pragma once
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player(SDL_Renderer* _renderer) : GameObject(_renderer)
	{
		// Set object type
		type = GameObjectType::Rectangle;
		// Load all necessary assets
		texture = util::loadTexture(renderer, TEXTURE_PATH);
		// Set member variables
		currentLives = MAX_LIVES;
		currentScore = 0;

		width = WIDTH;
		height = HEIGHT;
	}
	~Player()
	{
		// Free loaded images
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
	inline void render(util::Position _screenPosition, float widthFactor = 1.0, float heightFactor = 1.0)
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

		// Update velocity
		velocity = util::clamp(velocity - 1.f, MIN_VELOCITY, MAX_VELOCITY);
	}
	/// <summary>
	/// Add points to the player score.
	/// </summary>
	/// <param name="value">Value which is added to the score</param>
	inline void addToScore(int value)
	{
		currentScore += value;
	}
	/// <summary>
	/// Returns current score collected by the player.
	/// </summary>
	/// <returns></returns>
	inline int getCurrentScore()
	{
		return currentScore;
	}
	/// <summary>
	/// Returns current reamaining lives of the player.
	/// </summary>
	/// <returns></returns>
	inline int getCurrentLives()
	{
		return currentLives;
	}
	/// <summary>
	/// Reduces current reamaining lives by one.
	/// </summary>
	inline void reduceLives()
	{
		currentLives -= 1;
	}
	/// <summary>
	/// Determines whether the player is dead or not.
	/// </summary>
	/// <returns></returns>
	inline bool isDead()
	{
		return currentLives == 0;
	}
	inline void turnOffAcceleration()
	{
		acceleration = 0.f;
	}
	inline void increaseAcceleration(bool isNegativeXAxis)
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
	inline float getVelocity()
	{
		velocity = util::clamp(velocity + acceleration, MIN_VELOCITY, MAX_VELOCITY);
		return velocity * velocityMultiplier;
	}
private:
	const std::string TEXTURE_PATH = "GameObjects/Player.png";
	const int MAX_LIVES = 3;

	const float WIDTH = 100.f;
	const float HEIGHT = 20.f;

	SDL_Texture* texture;

	int currentLives;
	int currentScore;

	const float MIN_VELOCITY = 5.f;
	const float MAX_VELOCITY = 20.f;
	float acceleration = 0.f;
	float velocity = MIN_VELOCITY;
	float velocityMultiplier = -1.f;
};

