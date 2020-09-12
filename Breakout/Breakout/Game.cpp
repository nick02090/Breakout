#include "Game.h"
#include "MainMenuGameScene.h"
#include "StoryGameScene.h"
#include "ArcadeGameScene.h"

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
		gameState = GameState::MainMenu;
		initScene();
		// Hide cursor
		SDL_ShowCursor(SDL_DISABLE);
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
		gameScene->handleInput(&e);
		quit = gameScene->hasRequestedToQuit();
		if (quit)
		{
			break;
		}
		// Change scene if it was requested
		if (gameScene->hasRequestNextGameState())
		{
			// Get next scene and initialize it
			gameState = gameScene->getNextGameState();
			initScene();
		}

		// Clear the screen
		SDL_RenderClear(renderer);

		// Calculate deltaTime
		last = now;
		now = static_cast<int>(SDL_GetPerformanceCounter());
		deltaTime = (float)((now - last) * 1000 / (float)SDL_GetPerformanceFrequency());

		// Render screen for the current scene
		gameScene->update(deltaTime);

		// Update the screen
		SDL_RenderPresent(renderer);

		// Calculate FPS
		fps++;
		currentTime = SDL_GetTicks();
		int diff = currentTime - previousTime;
		if (diff > 1000)
		{
			previousTime = currentTime;
			fpsPrint = fps;
			fps = 0;
		}
		if (showFps)
		{
			std::cout << "FPS: " << fpsPrint << std::endl;
		}
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
	Mix_Quit();
	SDL_Quit();
}

bool Game::initSDL()
{
	// Initialization flag
	bool success = true;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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

				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

void Game::initScene()
{
	delete gameScene;

	switch (gameState)
	{
	case GameState::MainMenu:
		gameScene = new MainMenuGameScene(renderer);
		break;
	case GameState::Story:
		gameScene = new StoryGameScene(renderer);
		break;
	case GameState::Arcade:
		gameScene = new ArcadeGameScene(renderer);
		break;
	default:
		std::cout << "Invalid game state!" << std::endl;
		break;
	}

	// Load necessary media assets for the new scene
	if (!gameScene->loadMedia())
	{
		std::cout << "Failed to load media!" << std::endl;
	}
}