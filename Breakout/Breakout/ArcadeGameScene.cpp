#include "ArcadeGameScene.h"

ArcadeGameScene::ArcadeGameScene(SDL_Renderer* _renderer) : GameScene(_renderer)
{
	player = new Player(renderer);
	levelGenerator = new LevelGenerator(renderer);
	level = levelGenerator->generate(player);
	// Load the level media
	if (!level->loadMedia())
	{
		std::cout << "Failed to load the level media!" << std::endl;
	}
	saveData = util::loadSaveData();
}

ArcadeGameScene::~ArcadeGameScene()
{
	delete player;
	delete levelGenerator;
}

void ArcadeGameScene::update(float deltaTime)
{
	// Render the level on a screen
	level->update(deltaTime);
}

void ArcadeGameScene::handleInput(SDL_Event* e)
{
	// Let level handle it's own input
	level->handleInput(e);
	// Check if level has ended
	if (level->hasEnded())
	{
		// Check if player has gotten a new high score
		if (player->getCurrentScore() > saveData.highScore)
		{
			saveData.highScore = player->getCurrentScore();
			util::saveSaveData(saveData);
		}
		// Generate a new one
		level = levelGenerator->generate(player);
		// Load the level media
		if (!level->loadMedia())
		{
			std::cout << "Failed to load the level media!" << std::endl;
		}
	}
	// Check if level requested to quit the whole game
	if (level->hasRequestedQuit())
	{
		// Delete the level
		delete level;
		// Request a quit application
		shouldQuit = true;
	}
	// Check if level requested to go to main menu
	if (level->hasRequestedMainMenu())
	{
		// Delete the level
		delete level;
		// Request MainMenu
		nextGameState = GameState::MainMenu;
	}
}

bool ArcadeGameScene::loadMedia()
{
	return true;
}
