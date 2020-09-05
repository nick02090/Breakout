#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

enum class GameState
{
	MAIN_MENU,
	STORY,
	ARCADE,
	COOP,
	DEFAULT
};


class GameScene
{
public:
	GameScene(SDL_Renderer* _renderer) : renderer(_renderer) 
	{
		// Initialize screenWidth and screenHeight
		SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);

		// Initialize nextGameState
		nextGameState = GameState::DEFAULT;
	}
	virtual ~GameScene() {}
	/// <summary>
	/// Updates the screen window.
	/// </summary>
	virtual void update() = 0;
	/// <summary>
	/// Handles input.
	/// </summary>
	virtual void handleInput(SDL_Event* e) = 0;
	/// <summary>
	/// Loads required media.
	/// </summary>
	virtual bool loadMedia() = 0;
	/// <summary>
	/// Returns current should quit state.
	/// </summary>
	/// <returns></returns>
	bool hasRequestedToQuit()
	{
		return shouldQuit;
	}
	/// <summary>
	/// Returns true if the scene has request to change to another one.
	/// </summary>
	/// <returns></returns>
	bool hasRequestNextGameState()
	{
		// If nextGameState has been set then the scene requested a change
		if (nextGameState != GameState::DEFAULT)
		{
			return true;
		}
		else 
		{
			return false;
		}
	}
	/// <summary>
	/// Returns next game state.
	/// </summary>
	/// <returns></returns>
	GameState getNextGameState()
	{
		return nextGameState;
	}
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
	bool shouldQuit = false;
	GameState nextGameState;
};

