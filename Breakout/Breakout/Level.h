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
		WinEndMenu,
		LoseEndMenu,
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
	void update(float deltaTime);
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
	/// <summary>
	/// Ends level.
	/// </summary>
	void end();

	/// <summary>
	/// Determines whether the level can be replayed during or at the end of it.
	/// </summary>
	bool isRetryable;

	/// <summary>
	/// Path of the HUD overlay texture.
	/// </summary>
	const std::string HUDTexturePath = "Textures/LevelHUD.png";
	
	/// <summary>
	/// Maximum width of the screen that can be used for rendering bricks layout.
	/// </summary>
	const float MaxBricksWidth = 1004.f;
	/// <summary>
	/// Maximum height of the screen that can be used for rendering bricks layout.
	/// </summary>
	const float MaxBricksHeight = 600.f;
	/// <summary>
	/// Height of a one unscaled brick.
	/// </summary>
	const float BrickHeight = 20.f;
	/// <summary>
	/// Widht of a one unscaled brick.
	/// </summary>
	const float BrickWidth = 50.f;
	/// <summary>
	/// Factor that scales bricks width.
	/// </summary>
	float bricksWidthFactor;
	/// <summary>
	/// Factor that scales bricks height.
	/// </summary>
	float bricksHeightFactor;

	int rowCount;
	int columnCount;
	int rowSpacing;
	int columnSpacing;
	std::string backgroundTexturePath;
	std::string backgroundMusicPath;
	std::vector<std::vector<Brick*>> bricksLayout;
	std::vector<Brick*> bricks;
	std::string name;

	Player* player;
	Ball* ball;

	util::Position currentPlayerPosition = {445.f, 660.f};
	util::Position currentBallPosition = {485.f, 618.f};
	util::Position firstBrickPosition = {10.f, 10.f};
	std::vector<std::vector<util::Position>> bricksPositions;

	float currentBallDirectionX = 1.f;
	float currentBallDirectionY = -1.f;

	LevelState levelState = LevelState::Playing;

	SDL_Texture* backgroundTexture = NULL;
	SDL_Texture* HUDTexture = NULL;
	Mix_Music* backgroundMusic = NULL;

	// HINT: Pause/EndLevel menu is designed to have maximum of three buttons -> thus Top, Middle, Bottom.
	// Positions of the buttons on the pause menu.
	const util::Position TopButtonPosition = { 365.f, 250.f };
	const util::Position MiddleButtonPosition = { 365.f, 350.f };
	const util::Position BottomButtonPosition = { 365.f, 450.f };
	// Positions of the text of the buttons on the pause menu.
	const util::Position TopTextPosition = { 420.f, 270.f };
	const util::Position MiddleTextPosition = { 440.f, 370.f };
	const util::Position BottomTextPosition = { 450.f, 470.f };

	// Pause menu and its properties.
	Menu<Level>* pauseMenu;
	std::vector<MenuButton> retryablePauseMenuButtons {
		{ TopButtonPosition, TopTextPosition, "RESUME" },
		{ MiddleButtonPosition, MiddleTextPosition, "RETRY" },
		{ BottomButtonPosition, BottomTextPosition, "QUIT" }
	};
	std::vector<MenuButton> nonRetryablePauseMenuButtons{
		{ TopButtonPosition, TopTextPosition, "RESUME" },
		{ MiddleButtonPosition, MiddleTextPosition, "QUIT" }
	};
	Menu<Level>::MenuRequest retryablePauseMenuRequests[3] = { &Level::resume, &Level::retry, &Level::quit };
	Menu<Level>::MenuRequest nonRetryablePauseMenuRequests[2] = { &Level::resume, &Level::quit };

	// Lose End Level menu and its properties.
	Menu<Level>* loseEndLevelMenu;
	std::vector<MenuButton> retryableLoseEndLevelMenuButtons{
		{ TopButtonPosition, TopTextPosition, "RETRY" },
		{ MiddleButtonPosition, MiddleTextPosition, "QUIT" }
	};
	Menu<Level>* nonRetryableLoseEndLevelMenu;
	std::vector<MenuButton> nonRetryableLoseEndLevelMenuButtons{
		{ TopButtonPosition, TopTextPosition, "QUIT" }
	};
	Menu<Level>::MenuRequest retryableLoseEndLevelMenuRequests[2] = { &Level::retry, &Level::quit };
	Menu<Level>::MenuRequest nonRetryableLoseEndLevelMenuRequests[1] = { &Level::quit };

	// Win End Level menu and its properties.
	Menu<Level>* winEndLevelMenu;
	std::vector<MenuButton> winEndLevelMenuButtons{
		{ TopButtonPosition, TopTextPosition, "RESUME" },
		{ MiddleButtonPosition, MiddleTextPosition, "QUIT" }
	};
	Menu<Level>::MenuRequest winEndLevelMenuRequests[2] = { &Level::end, &Level::quit };

	TTF_Font* font = NULL;

	SDL_Renderer* renderer;
};

