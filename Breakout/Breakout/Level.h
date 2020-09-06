#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Brick.h"
#include "tinyxml2.h"
#include <sstream>
#include <string>
#include "Utilities.h"
namespace util
{
	class Array2D;
}

class Level
{
public:

	enum class LevelState {
		PLAYING,
		PAUSED,
		END,
		QUIT,
		MAINMENU
	};

	Level(std::string path, SDL_Renderer* _renderer);
	~Level()
	{
		// Free loaded images
		SDL_DestroyTexture(backgroundTexture);
		backgroundTexture = NULL;
		SDL_DestroyTexture(blackButtonTexture);
		blackButtonTexture = NULL;
		SDL_DestroyTexture(whiteButtonTexture);
		whiteButtonTexture = NULL;
		SDL_DestroyTexture(HUDTexture);
		HUDTexture = NULL;

		// Free loaded font
		TTF_CloseFont(font);
		font = NULL;
	}
	bool loadMedia();
	void update();
	void handleInput(SDL_Event* e);
	/// <summary>
	/// Determines whether the level has ended.
	/// </summary>
	/// <returns></returns>
	bool hasEnded()
	{
		return levelState == LevelState::END;
	}
	/// <summary>
	/// Determines whether user requested to quit the whole game.
	/// </summary>
	/// <returns></returns>
	bool hasRequestedQuit()
	{
		return levelState == LevelState::QUIT;
	}
	/// <summary>
	/// Determines whether user request to go back to main menu
	/// </summary>
	/// <returns></returns>
	bool hasRequestedMainMenu()
	{
		return levelState == LevelState::MAINMENU;
	}
private:
	const std::string HUDTexturePath = "Textures/LevelHUD.png";

	int rowCount;
	int columnCount;
	int rowSpacing;
	int columnSpacing;
	std::string backgroundTexturePath;
	std::vector<std::vector<std::string>> bricksLayout;
	std::vector<Brick*> bricks;

	LevelState levelState = LevelState::PLAYING;

	SDL_Texture* backgroundTexture = NULL;
	SDL_Texture* blackButtonTexture = NULL;
	SDL_Texture* whiteButtonTexture = NULL;
	SDL_Texture* HUDTexture = NULL;

	TTF_Font* font = NULL;

	SDL_Renderer* renderer;
};

