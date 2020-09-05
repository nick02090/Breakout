#include "MainMenuGameScene.h"
#include "Utilities.h"
#include <iostream>

void MainMenuGameScene::update()
{
	// Render texture to screen
	SDL_RenderCopy(renderer, texture, NULL, NULL);
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
	texture = util::loadTexture(renderer, "Textures/Background/MainMenu.png");
	if (texture == NULL)
	{
		std::cout << "Failed to load texture image!" << std::endl;
		success = false;
	}

	return success;
}
