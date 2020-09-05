#include "MainMenuGameScene.h"
#include "Utilities.h"
#include <iostream>

void MainMenuGameScene::update()
{
	// Render background texture to screen
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	// Render UI to screen
	switch (mainMenuState)
	{
	case MainMenuGameScene::MainMenuState::FIRST_MENU:
		// Draw PLAY button
		drawButton(blackButtonTexture, PLAY_BUTTON_POSITION);
		// Draw QUIT button
		drawButton(blackButtonTexture, QUIT_BUTTON_POSITION);
		break;
	case MainMenuGameScene::MainMenuState::SECOND_MENU:
		// Draw PLAY button
		drawButton(blackButtonTexture, PLAY_BUTTON_POSITION);
		// Draw QUIT button
		drawButton(blackButtonTexture, QUIT_BUTTON_POSITION);
		// Draw STORY button
		drawButton(blackButtonTexture, STORY_BUTTON_POSITION);
		// Draw ARCADE button
		drawButton(blackButtonTexture, ARCADE_BUTTON_POSITION);
		// Draw CO-OP button
		drawButton(blackButtonTexture, COOP_BUTTON_POSITION);
		break;
	default:
		std::cout << "Invalid MainMenuState!" << std::endl;
		break;
	}

	// Add extra layer to selected button
	drawButton(whiteButtonTexture, selectedButtonPosition);

	// Add extra layer to previous state selected button if there is one
	if (isValidPosition(previousStateButtonPosition))
	{
		drawButton(orangeButtonTexture, previousStateButtonPosition);
	}

	// Add text to buttons
}

bool MainMenuGameScene::handleInput(SDL_Event* e)
{
	// Handle events on the queue
	while (SDL_PollEvent(e) != 0)
	{
		// User request quit
		if (e->type == SDL_QUIT)
		{
			return true;
		}
		// User presses a key
		else if (e->type == SDL_KEYDOWN)
		{
			switch (e->key.keysym.sym)
			{
			default:
				break;
			}
		}
	}

	return false;
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

	// Load MainMenu background
	blackButtonTexture = util::loadTexture(renderer, "UI/Textures/Buttons/BlackButton.png");
	if (blackButtonTexture == NULL)
	{
		std::cout << "Failed to load texture image!" << std::endl;
		success = false;
	}

	// Load MainMenu background
	whiteButtonTexture = util::loadTexture(renderer, "UI/Textures/Buttons/WhiteButton.png");
	if (whiteButtonTexture == NULL)
	{
		std::cout << "Failed to load texture image!" << std::endl;
		success = false;
	}

	// Load MainMenu background
	orangeButtonTexture = util::loadTexture(renderer, "UI/Textures/Buttons/OrangeButton.png");
	if (orangeButtonTexture == NULL)
	{
		std::cout << "Failed to load texture image!" << std::endl;
		success = false;
	}

	return success;
}

void MainMenuGameScene::drawButton(SDL_Texture* texture, Position position)
{
	SDL_Rect rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.w = 270;
	rect.h = 70;
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}