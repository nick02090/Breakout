#include "StoryGameScene.h"

void StoryGameScene::update()
{
	switch (storyState)
	{
	// Render update if story is in narration mode
	case StoryGameScene::StoryState::NARRATION:
		narrationUpdate();
		break;
	// Render update if story is in playing level mode
	case StoryGameScene::StoryState::PLAY:
		playUpdate();
		break;
	// Render update if story is in paused from playing level mode
	case StoryGameScene::StoryState::PAUSE:
		pauseUpdate();
		break;
	default:
		break;
	}
}

void StoryGameScene::handleInput(SDL_Event* e)
{
	switch (storyState)
	{
	// Handle input if story is in narration mode
	case StoryGameScene::StoryState::NARRATION:
		narrationHandleInput(e);
		break;
	// Handle input if story is in playing level mode
	case StoryGameScene::StoryState::PLAY:
		playHandleInput(e);
		break;
	// Handle input if story is in paused from playing level mode
	case StoryGameScene::StoryState::PAUSE:
		pauseHandleInput(e);
		break;
	default:
		break;
	}
}

bool StoryGameScene::loadMedia()
{
	// Loading success flag
	bool success = true;

	// Load StoryTransition background
	backgroundTransitionTexture = loadTexture("Textures/Background/StoryTransition.png");
	if (backgroundTransitionTexture == NULL)
	{
		std::cout << "Failed to load texture image!" << std::endl;
		success = false;
	}

	// Load black button background
	blackButtonTexture = loadTexture("UI/Textures/Buttons/BlackButton.png");
	if (blackButtonTexture == NULL)
	{
		std::cout << "Failed to load texture image!" << std::endl;
		success = false;
	}

	// Load white button background
	whiteButtonTexture = loadTexture("UI/Textures/Buttons/WhiteButton.png");
	if (whiteButtonTexture == NULL)
	{
		std::cout << "Failed to load texture image!" << std::endl;
		success = false;
	}

	// Load the font
	font = TTF_OpenFont("Fonts/p5hatty.ttf", HEADING_FONT_SIZE);
	if (font == NULL)
	{
		std::cout << "Failed to load font! SDL_Error: " << TTF_GetError() << std::endl;
		success = false;
	}

	return success;
}

void StoryGameScene::narrationHandleInput(SDL_Event* e)
{
	// Handle events on the queue
	while (SDL_PollEvent(e) != 0)
	{
		// User request quit
		if (e->type == SDL_QUIT) {
			shouldQuit = true;
		}
		// User presses a key
		if (e->type == SDL_KEYDOWN)
		{
			switch (e->key.keysym.sym)
			{
			case SDLK_RETURN:
				currentChapterLine = chapters[currentChapterIndex]->getNextLine();
				if (currentChapterLine._Equal("PLAY"))
				{
					storyState = StoryState::PLAY;
					currentLevel = new Level(chapters[currentChapterIndex]->getPathToLevel());
				}
				else if (currentChapterLine._Equal("END"))
				{
					currentChapterIndex += 1;
					if (currentChapterIndex == 3)
					{
						// Finished all of the chapters, return to the MainMenu
						nextGameState = GameState::MAIN_MENU;
					}
				}
				break;
			default:
				break;
			}
		}
	}
}

void StoryGameScene::playHandleInput(SDL_Event* e)
{
	// Handle events on the queue
	while (SDL_PollEvent(e) != 0)
	{
		// User request quit
		if (e->type == SDL_QUIT) {
			shouldQuit = true;
		}
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

void StoryGameScene::pauseHandleInput(SDL_Event* e)
{
	// Handle events on the queue
	while (SDL_PollEvent(e) != 0)
	{
		// User request quit
		if (e->type == SDL_QUIT) {
			shouldQuit = true;
		}
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

void StoryGameScene::narrationUpdate()
{
	// Render background texture to screen
	SDL_RenderCopy(renderer, backgroundTransitionTexture, NULL, NULL);

	// Draw title
	SDL_Color white = {250, 250, 250};
	drawText(font, white, chapters[currentChapterIndex]->getTitle().c_str(), {screenWidth/10, screenHeight/10}, HEADING_FONT_SIZE);

	// Draw text
	drawText(font, white, currentChapterLine.c_str(), {screenWidth/10, screenHeight/2}, PARAGRAPH_FONT_SIZE);

	// Draw confirm button and it's text
	SDL_Color black = { 0, 0, 0 };
	drawButton(whiteButtonTexture, {750, 700});
	drawText(font, black, "OK", {850, 720}, HEADING_FONT_SIZE);
}

void StoryGameScene::playUpdate()
{
	// Render background texture to screen

	// Play the level
}

void StoryGameScene::pauseUpdate()
{
	// Pause everything

	// Dim the current screen

	// Draw text
	// "PAUSED"
	// continue
	//  quit
}
