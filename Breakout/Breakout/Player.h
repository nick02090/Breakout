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
	}
	~Player()
	{
		// Free loaded images
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
	inline void render(util::Position screenPosition, float widthFactor = 1.0, float heightFactor = 1.0)
	{
		// Create a rect to position the texture
		SDL_Rect rect;
		rect.x = screenPosition.x;
		rect.y = screenPosition.y;
		rect.w = static_cast<int>(WIDTH / widthFactor);
		rect.h = static_cast<int>(HEIGHT / heightFactor);

		// Render the texture on the screen
		SDL_RenderCopy(renderer, texture, NULL, &rect);
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
private:
	const std::string TEXTURE_PATH = "GameObjects/Player.png";
	const int MAX_LIVES = 3;

	const int WIDTH = 100;
	const int HEIGHT = 20;

	SDL_Texture* texture;

	int currentLives;
	int currentScore;
};

