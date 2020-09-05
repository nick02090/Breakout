#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
class GameScene
{
public:
	GameScene(SDL_Renderer* _renderer) : renderer(_renderer) 
	{
		SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);
	}
	~GameScene() {}
	/// <summary>
	/// Updates the screen window.
	/// </summary>
	virtual void update() = 0;
	/// <summary>
	/// Handles input.
	/// </summary>
	virtual bool handleInput(SDL_Event* e) = 0;
	/// <summary>
	/// Loads required media.
	/// </summary>
	virtual bool loadMedia() = 0;
protected:

	struct Position
	{
		int x;
		int y;
	};

	/// <summary>
	/// Determines whether the given position is within the screen range.
	/// </summary>
	/// <param name="position"></param>
	/// <returns></returns>
	bool isValidPosition(Position position)
	{
		bool isValid = true;

		// It's not valid if it is below zero
		if (position.x < 0 || position.y < 0)
		{
			isValid = false;
		}
		// It's not valid if it is outside of the window screen size
		else if (position.x > screenWidth || position.y > screenHeight)
		{
			isValid = false;
		}

		return isValid;
	}

	SDL_Renderer* renderer;
	int screenWidth, screenHeight;
};

