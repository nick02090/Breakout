#pragma once
#include "Utilities.h"
#include "Level.h"
#include "Player.h"
#include "Menu.h"

enum class GameState
{
	MainMenu,
	Story,
	Arcade,
	Coop,
	Default
};


class GameScene
{
public:
	GameScene(SDL_Renderer* _renderer);
	virtual ~GameScene();
	/// <summary>
	/// Updates the screen window.
	/// </summary>
	virtual void update(float deltaTime) = 0;
	/// <summary>
	/// Handles input.
	/// </summary>
	virtual void handleInput(SDL_Event* e, float deltaTime) = 0;
	/// <summary>
	/// Loads required media.
	/// </summary>
	virtual bool loadMedia() = 0;
	/// <summary>
	/// Returns current should quit state.
	/// </summary>
	/// <returns></returns>
	bool hasRequestedToQuit();
	/// <summary>
	/// Returns true if the scene has request to change to another one.
	/// </summary>
	/// <returns></returns>
	bool hasRequestNextGameState();
	/// <summary>
	/// Returns next game state.
	/// </summary>
	/// <returns></returns>
	GameState getNextGameState();
protected:
	SDL_Renderer* renderer;
	int screenWidth, screenHeight;
	bool shouldQuit = false;
	GameState nextGameState;
};

