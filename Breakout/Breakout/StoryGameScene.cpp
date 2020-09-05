#include "StoryGameScene.h"

void StoryGameScene::update()
{

}

void StoryGameScene::handleInput(SDL_Event* e)
{
	// Handle events on the queue
	while (SDL_PollEvent(e) != 0)
	{
		// User presses a key
		if (e->type == SDL_KEYDOWN)
		{
			switch (e->key.keysym.sym)
			{
			default:
				break;
			}
		}
	}
}

bool StoryGameScene::loadMedia()
{
	// Loading success flag
	bool success = true;



	return success;
}
