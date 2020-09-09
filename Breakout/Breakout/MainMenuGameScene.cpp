#include "MainMenuGameScene.h"

void MainMenuGameScene::update()
{
	// Render background texture to screen
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	// Render menus
	firstMenu->update();
	secondMenu->update();
}

void MainMenuGameScene::handleInput(SDL_Event* e)
{
	// Let current menu handle the input
	currentMenu->handleInput(e);

	// Quit if current menu has requested to quit
	shouldQuit = currentMenu->hasRequestedQuit();

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

	// User has made a selection on the current menu
	// Invoke requested method
	int requestedElementIndex = currentMenu->confirmSelection();
	if (requestedElementIndex >= 0)
	{
		std::invoke(currentMenuRequests[requestedElementIndex], this);
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
	currentMenu = secondMenu;
	currentMenuRequests = secondMenuRequests;
	firstMenu->show();
	secondMenu->show();
}

void MainMenuGameScene::quit()
{
	shouldQuit = true;
}

void MainMenuGameScene::story()
{
	nextGameState = GameState::STORY;
}

void MainMenuGameScene::arcade()
{
	nextGameState = GameState::ARCADE;
}

void MainMenuGameScene::coop()
{
	nextGameState = GameState::COOP;
}
