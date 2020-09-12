#include "MainMenuGameScene.h"

MainMenuGameScene::MainMenuGameScene(SDL_Renderer* _renderer) : GameScene(_renderer)
{
	// Initialize member variables
	firstMenu = new Menu<MainMenuGameScene>(firstMenuButtons, renderer, firstMenuRequests, this);
	secondMenu = new Menu<MainMenuGameScene>(secondMenuButtons, renderer, secondMenuRequests, this);
	currentMenu = firstMenu;
	currentMenu->show();

	// Initialize textures
	backgroundTexture = NULL;

	// Initialize music
	backgroundMusic = NULL;
}

MainMenuGameScene::~MainMenuGameScene()
{
	// Free loaded images
	SDL_DestroyTexture(backgroundTexture);
	backgroundTexture = NULL;

	//Free the music
	Mix_FreeMusic(backgroundMusic);
	backgroundMusic = NULL;

	// Delete menus
	currentMenu = NULL;
	delete firstMenu;
	firstMenu = NULL;
	delete secondMenu;
	secondMenu = NULL;
	// Delete menu buttons
	firstMenuButtons.clear();
	secondMenuButtons.clear();
}

void MainMenuGameScene::update(float deltaTime)
{
	// If there is no music playing
	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(backgroundMusic, -1);
		// Max volume
		Mix_VolumeMusic(MIX_MAX_VOLUME);
	}

	// Render background texture to screen
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	// Render menus
	firstMenu->update(deltaTime);
	secondMenu->update(deltaTime);
}

void MainMenuGameScene::handleInput(SDL_Event* e)
{
	// Let current menu handle the input
	currentMenu->handleInput(e);

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

	//Load MainMenu background music
	backgroundMusic = Mix_LoadMUS("Audio/Soundtracks/bensound-hipjazz.mp3");
	if (backgroundMusic == NULL)
	{
		std::cout << "Failed to load background music!" << std::endl;
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
