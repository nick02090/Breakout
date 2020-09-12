#include "MainMenuGameScene.h"

MainMenuGameScene::MainMenuGameScene(SDL_Renderer* _renderer) : GameScene(_renderer)
{
	// Initialize member variables
	firstMenu = new Menu<MainMenuGameScene>(firstMenuButtons, renderer, firstMenuRequests, this);
	secondMenu = new Menu<MainMenuGameScene>(secondMenuButtons, renderer, secondMenuRequests, this);
	currentMenu = firstMenu;
	currentMenuRequests = firstMenuRequests;
	currentMenu->show();

	// Initialize textures
	backgroundTexture = NULL;
}

MainMenuGameScene::~MainMenuGameScene()
{
	// Free loaded images
	SDL_DestroyTexture(backgroundTexture);
	backgroundTexture = NULL;
}

void MainMenuGameScene::update(float deltaTime)
{
	// Render background texture to screen
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	// Render menus
	firstMenu->update(deltaTime);
	secondMenu->update(deltaTime);
}

void MainMenuGameScene::handleInput(SDL_Event* e, float deltaTime)
{
	// Let current menu handle the input
	currentMenu->handleInput(e, deltaTime);

	// Quit if current menu has requested to quit (or it was already called upon)
	shouldQuit = currentMenu->hasRequestedQuit() | shouldQuit;

	// Reverse is called upon a BACKSPACE 
	// Occurs when a second menu wants to pass back controls to the first menu
	if (currentMenu->hasRequestedReverse())
	{
		firstMenu->reset();
		secondMenu->reset();
		firstMenu->show();
		currentMenu = firstMenu;
		currentMenuRequests = firstMenuRequests;
	}
}

bool MainMenuGameScene::loadMedia()
{
	// Loading success flag
	bool success = true;

	// Load MainMenu background
	backgroundTexture = util::loadTexture(renderer, "Textures/Background/MainMenu.png");
	if (backgroundTexture == NULL)
	{
		std::cout << "Failed to load texture image!" << std::endl;
		success = false;
	}

	// Load media for the menus
	firstMenu->loadMedia();
	secondMenu->loadMedia();

	return success;
}

void MainMenuGameScene::play()
{
	// Show the next menu that chooses what to play
	currentMenu = secondMenu;
	currentMenuRequests = secondMenuRequests;
	firstMenu->show();
	secondMenu->show();
}

void MainMenuGameScene::quit()
{
	// Quit the application
	shouldQuit = true;
}

void MainMenuGameScene::story()
{
	// Play story mode
	nextGameState = GameState::Story;
}

void MainMenuGameScene::arcade()
{
	// Play arcade mode
	nextGameState = GameState::Arcade;
}

void MainMenuGameScene::coop()
{
	// Play coop mode
	nextGameState = GameState::Coop;
}
