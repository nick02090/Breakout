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
	switch (mainMenuState)
	{
	case MainMenuGameScene::MainMenuState::FIRST_MENU:
		// Draw PLAY text
		drawText(getTextColor(PLAY_BUTTON_POSITION), "PLAY", PLAY_TEXT_POSITION);
		// Draw QUIT text
		drawText(getTextColor(QUIT_BUTTON_POSITION), "QUIT", QUIT_TEXT_POSITION);
		break;
	case MainMenuGameScene::MainMenuState::SECOND_MENU:
		// Draw PLAY text
		drawText(getTextColor(PLAY_BUTTON_POSITION), "PLAY", PLAY_TEXT_POSITION);
		// Draw QUIT text
		drawText(getTextColor(QUIT_BUTTON_POSITION), "QUIT", QUIT_TEXT_POSITION);
		// Draw STORY text
		drawText(getTextColor(STORY_BUTTON_POSITION), "STORY", STORY_TEXT_POSITION);
		// Draw ARCADE text
		drawText(getTextColor(ARCADE_BUTTON_POSITION), "ARCADE", ARCADE_TEXT_POSITION);
		// Draw CO-OP text
		drawText(getTextColor(COOP_BUTTON_POSITION), "CO-OP", COOP_TEXT_POSITION);
		break;
	default:
		std::cout << "Invalid MainMenuState!" << std::endl;
		break;
	}
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

	// Load the font
	font = TTF_OpenFont("Fonts/p5hatty.ttf", 48);
	if (font == NULL)
	{
		std::cout << "Failed to load font! SDL_Error: " << TTF_GetError() << std::endl;
		success = false;
	}

	return success;
}

void MainMenuGameScene::drawButton(SDL_Texture* texture, Position position)
{
	// Create a rect to position the texture
	SDL_Rect rect;
	rect.x = position.x;
	rect.y = position.y;
	rect.w = 270;
	rect.h = 70;

	// Render the texture on the screen
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void MainMenuGameScene::drawText(SDL_Color color, const char* message, Position position)
{
	// Create surface to put text on
	SDL_Surface* messageSurface = TTF_RenderText_Solid(font, message, color);

	// Convert the surface to a texture
	SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);

	// Create a rect to position the texture
	SDL_Rect messageRect;
	messageRect.x = position.x;
	messageRect.y = position.y;
	messageRect.w = std::strlen(message) * 25;
	messageRect.h = 40;

	// Render the texture on the screen
	SDL_RenderCopy(renderer, messageTexture, NULL, &messageRect);

	// Get rid of the surface and the texture
	SDL_FreeSurface(messageSurface);
	SDL_DestroyTexture(messageTexture);
}

SDL_Color MainMenuGameScene::getTextColor(Position buttonPosition)
{
	// If the button position is the same as the currently selected button position return black color
	if (selectedButtonPosition.x == buttonPosition.x && selectedButtonPosition.y == buttonPosition.y)
	{
		SDL_Color blackColor = { 0, 0, 0 };
		return blackColor;
	}
	// If the previous state selected button position is the same as the given position return black color
	else if (previousStateButtonPosition.x == buttonPosition.x && previousStateButtonPosition.y == buttonPosition.y)
	{
		SDL_Color blackColor = { 0, 0, 0 };
		return blackColor;
	}
	else
	{
		SDL_Color whiteColor = { 250, 250, 250 };
		return whiteColor;
	}
}