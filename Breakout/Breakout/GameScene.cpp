#include "GameScene.h"

GameScene::GameScene(SDL_Renderer* _renderer) : renderer(_renderer)
{
	// Initialize screenWidth and screenHeight
	SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);

	// Initialize nextGameState
	nextGameState = GameState::Default;
}

GameScene::~GameScene()
{
}

bool GameScene::hasRequestedToQuit()
{
	return shouldQuit;
}

bool GameScene::hasRequestNextGameState()
{
	// If nextGameState has been set then the scene requested a change
	if (nextGameState != GameState::Default)
	{
		return true;
	}
	else
	{
		return false;
	}
}

GameState GameScene::getNextGameState()
{
	return nextGameState;
}