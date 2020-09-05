#include "Game.h"
#include <iostream>
#include "MainMenuGameScene.h"

Game::Game() 
{
	// Start up SDL and create a window.
	if (!initSDL()) 
	{
		std::cout << "Failed to initialize SDL!" << std::endl;
	} 
	else
	{
		// Initialize startup scene (MainMenu)
		gameState = GameState::MAIN_MENU;
		initScene();
		// Load necessary media assets for the scene
		if (!gameScene->loadMedia()) 
		{
			std::cout << "Failed to load media!" << std::endl;
		}
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
		// Handle input for the current scene
		quit = gameScene->handleInput(&e);

		// Clear the screen
		SDL_RenderClear(renderer);

		// Render screen for the current scene
		gameScene->update();

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

	// Destroy GameScene
	delete gameScene;

	// Quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
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

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					std::cout << "SDL_ttf could not be initiliazed! SDL_Error: " << TTF_GetError() << std::endl;
					success = false;
				}
			}
		}
	}

	return success;
}

void Game::initScene()
{
	switch (gameState)
	{
	case GameState::MAIN_MENU:
		gameScene = new MainMenuGameScene(renderer);
		break;
	case GameState::LOSE_LEVEL:
		break;
	case GameState::PAUSED_LEVEL:
		break;
	case GameState::PLAYING_LEVEL:
		break;
	case GameState::WIN_LEVEL:
		break;
	default:
		break;
	}
}