#pragma once
#include <SDL_ttf.h>
class SDL_Window;
class SDL_Renderer;

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
	void update();
private:
	bool initSDL();
	/// <summary>
	/// Frees media and shuts down SDL.
	/// </summary>
	void end();

	int screenWidth = 1024;
	int screenHeight = 768;
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;
	GameState gameState;
};