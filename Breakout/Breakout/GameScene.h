#pragma once
#include "Utilities.h"
#include "Level.h"
#include "Player.h"
#include "Menu.h"

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
	SDL_Renderer* renderer;
	int screenWidth, screenHeight;
	bool shouldQuit = false;
	GameState nextGameState;
};

