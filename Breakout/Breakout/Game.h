#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "GameScene.h"

class Game
{
public:

	enum class GameState
	{
		PLAYING_LEVEL,
		PAUSED_LEVEL,
		MAIN_MENU,
		WIN_LEVEL,
		LOSE_LEVEL
	};

	/// <summary>
	/// Initialize game and prepare everything for running.
	/// </summary>
	Game();
	/// <summary>
	/// Run game loop and display startup Main Menu.
	/// </summary>
	void start();
private:
	/// <summary>
	/// Initialize SDL and all of it's subsystems.
	/// </summary>
	/// <returns></returns>
	bool initSDL();
	/// <summary>
	/// Frees media and shuts down SDL.
	/// </summary>
	void end();
	/// <summary>
	/// Initializes a new scene based on a gameState.
	/// </summary>
	void initScene();

	int screenWidth = 1024;
	int screenHeight = 768;
	SDL_Window* window;
	SDL_Renderer* renderer;
	GameState gameState;
	GameScene* gameScene;
};