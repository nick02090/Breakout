#pragma once
#include <sstream>
#include <string>
#include "tinyxml2.h"
#include "Utilities.h"
#include "Brick.h"
#include "Player.h"
#include "Ball.h"
#include "Menu.h"
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

	Level(std::string path, SDL_Renderer* _renderer, Player* _player, std::string _name, bool _isRetryble);
	~Level()
	{
		// Free loaded images
		SDL_DestroyTexture(backgroundTexture);
		backgroundTexture = NULL;
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
	void resume();
	void retry();
	void quit();

	const std::string HUDTexturePath = "Textures/LevelHUD.png";
	
	const float MAX_BRICKS_WIDTH = 994.f;
	const float MAX_BRICKS_HEIGHT = 600.f;
	const float BRICK_HEIGHT = 20.f;
	const float BRICK_WIDHT = 50.f;
	float bricksWidthFactor;
	float bricksHeightFactor;

	int rowCount;
	int columnCount;
	int rowSpacing;
	int columnSpacing;
	std::string backgroundTexturePath;
	std::vector<std::vector<Brick*>> bricksLayout;
	std::vector<Brick*> bricks;

	Player* player;
	Ball* ball;

	util::Position currentPlayerPosition = {445.f, 660.f};
	util::Position currentBallPosition = {485.f, 618.f};
	util::Position firstBrickPosition = {15.f, 15.f};
	std::vector<std::vector<util::Position>> bricksPositions;

	float currentBallDirectionX = 1.f;
	float currentBallDirectionY = -1.f;

	std::string name;

	LevelState levelState = LevelState::PLAYING;

	SDL_Texture* backgroundTexture = NULL;
	SDL_Texture* HUDTexture = NULL;

	const util::Position RESUME_BUTTON_POSITION = { 365.f, 250.f };
	const util::Position RETRY_BUTTON_POSITION = { 365.f, 350.f };
	const util::Position QUIT_BUTTON_POSITION = { 365.f, 450.f };

	const util::Position RESUME_TEXT_POSITION = { 420.f, 270.f };
	const util::Position RETRY_TEXT_POSITION = { 440.f, 370.f };
	const util::Position QUIT_TEXT_POSITION = { 450.f, 470.f };

	Menu* pauseMenu;
	std::vector<MenuButton> retryablePauseMenuButtons {
		{ RESUME_BUTTON_POSITION, RESUME_TEXT_POSITION, "RESUME" },
		{ RETRY_BUTTON_POSITION, RETRY_TEXT_POSITION, "RETRY" },
		{ QUIT_BUTTON_POSITION, QUIT_TEXT_POSITION, "QUIT" }
	};
	std::vector<MenuButton> nonRetryablePauseMenuButtons{
		{ RESUME_BUTTON_POSITION, RESUME_TEXT_POSITION, "RESUME" },
		{ RETRY_BUTTON_POSITION, RETRY_TEXT_POSITION, "QUIT" }
	};

	typedef void (Level::* pauseMenuRequest)(void);
	pauseMenuRequest retryablePauseMenuRequests[3] = { &Level::resume, &Level::retry, &Level::quit };
	pauseMenuRequest nonRetryablePauseMenuRequests[2] = { &Level::resume, &Level::quit };

	bool isRetryable;

	TTF_Font* font = NULL;

	SDL_Renderer* renderer;
};

