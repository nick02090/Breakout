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
		Playing,
		Paused,
		End,
		Quit,
		MainMenu
	};

	Level(std::string path, SDL_Renderer* _renderer, Player* _player, std::string _name, bool _isRetryble);
	~Level();
	/// <summary>
	/// Loads required media.
	/// </summary>
	bool loadMedia();
	/// <summary>
	/// Updates the screen window.
	/// </summary>
	void update();
	/// <summary>
	/// Handles input.
	/// </summary>
	/// <param name="e"></param>
	void handleInput(SDL_Event* e);
	/// <summary>
	/// Determines whether the level has ended.
	/// </summary>
	/// <returns></returns>
	bool hasEnded();
	/// <summary>
	/// Determines whether user has requested to quit the whole game.
	/// </summary>
	/// <returns></returns>
	bool hasRequestedQuit();
	/// <summary>
	/// Determines whether user has requested to go back to main menu.
	/// </summary>
	/// <returns></returns>
	bool hasRequestedMainMenu();
private:
	/// <summary>
	/// Selected RESUME on the pause menu.
	/// </summary>
	void resume();
	/// <summary>
	/// Selected RETRY on the pause menu.
	/// </summary>
	void retry();
	/// <summary>
	/// Selected QUIT on the pause menu.
	/// </summary>
	void quit();

	const std::string HUDTexturePath = "Textures/LevelHUD.png";
	
	const float MaxBricksWidth = 994.f;
	const float MaxBricksHeight = 600.f;
	const float BrickHeight = 20.f;
	const float BrickWidth = 50.f;
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

	LevelState levelState = LevelState::Playing;

	SDL_Texture* backgroundTexture = NULL;
	SDL_Texture* HUDTexture = NULL;

	const util::Position ResumeButtonPosition = { 365.f, 250.f };
	const util::Position RetryButtonPosition = { 365.f, 350.f };
	const util::Position QuitButtonPosition = { 365.f, 450.f };

	const util::Position ResumeTextPosition = { 420.f, 270.f };
	const util::Position RetryTextPosition = { 440.f, 370.f };
	const util::Position QuitTextPosition = { 450.f, 470.f };

	Menu<Level>* pauseMenu;
	std::vector<MenuButton> retryablePauseMenuButtons {
		{ ResumeButtonPosition, ResumeTextPosition, "RESUME" },
		{ RetryButtonPosition, RetryTextPosition, "RETRY" },
		{ QuitButtonPosition, QuitTextPosition, "QUIT" }
	};
	std::vector<MenuButton> nonRetryablePauseMenuButtons{
		{ ResumeButtonPosition, ResumeTextPosition, "RESUME" },
		{ RetryButtonPosition, RetryTextPosition, "QUIT" }
	};

	Menu<Level>::MenuRequest retryablePauseMenuRequests[3] = { &Level::resume, &Level::retry, &Level::quit };
	Menu<Level>::MenuRequest nonRetryablePauseMenuRequests[2] = { &Level::resume, &Level::quit };

	bool isRetryable;

	TTF_Font* font = NULL;

	SDL_Renderer* renderer;
};

