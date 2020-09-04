#include "Game.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

Game::Game() 
{
	// Setup member variables.
	gameState = GameState::MAIN_MENU;
	// Start up SDL and create a window.
	if (!initSDL()) 
	{
		std::cout << "Failed to initialize SDL!" << std::endl;
	}
	else
	{
		// Load media
		// TODO: Needs to be implemented (load every asset at the beggining of the game)
	}
}


void Game::start()
{
	// Start main loop
	bool quit = false;

	// Event handler
	SDL_Event e;

	// While application is running
	while (!quit)
	{
		// Handle events on the queue
		while (SDL_PollEvent(&e) != 0)
		{
			// User request quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			// User presses a key
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				default:
					break;
				}
			}
		}

		// Clear the screen
		SDL_RenderClear(renderer);

		// Render texture to screen

		// Update the screen
		SDL_RenderPresent(renderer);
	}


	// Free resources and close SDL
	end();
}

void Game::end()
{
	// Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	// Destroy renderer
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Game::update()
{
	// TODO: Needs to be implemented
	// Handle input
}

bool Game::initSDL()
{
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not be initialized! SDL_Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		// Create a window
		window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else 
		{
			// Create a renderer for the window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
				success = false;
			}
			else 
			{
				// Initialize the renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					std::cout << "SDL_image could not be initialized! SDL_Error: " << IMG_GetError() << std::endl;
					success = false;
				}
			}
		}
	}

	return success;
}