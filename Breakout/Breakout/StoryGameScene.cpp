#include "StoryGameScene.h"

StoryGameScene::StoryGameScene(SDL_Renderer* _renderer) : GameScene(_renderer)
{
	// Initialize member variables
	storyState = StoryState::Narration;

	// Initialize the player
	player = new Player(_renderer);

	// Initialize textures
	backgroundTransitionTexture = NULL;
	blackButtonTexture = NULL;
	whiteButtonTexture = NULL;

	// Initialize chapters
	firstChapter = new StoryChapter(FirstChapterPath);
	secondChapter = new StoryChapter(SecondChapterPath);
	thirdChapter = new StoryChapter(ThirdChapterPath);
	chapters[0] = firstChapter;
	chapters[1] = secondChapter;
	chapters[2] = thirdChapter;
	StoryChapter* currentChapter = chapters[currentChapterIndex];
	currentChapterLine = currentChapter->getNextLine();
	currentLevel = NULL;

	// Initialize menu for narration mode
	narrationMenu = new Menu<StoryGameScene>(narrationMenuButtons, renderer, narrationMenuRequests, this);
	narrationMenu->show();

	// Initialize font
	font = NULL;
}

StoryGameScene::~StoryGameScene()
{
	// Free loaded images
	SDL_DestroyTexture(backgroundTransitionTexture);
	backgroundTransitionTexture = NULL;
	SDL_DestroyTexture(blackButtonTexture);
	blackButtonTexture = NULL;
	SDL_DestroyTexture(whiteButtonTexture);
	whiteButtonTexture = NULL;

	// Delete the player
	delete player;

	// Free loaded font
	TTF_CloseFont(font);
	font = NULL;
}

void StoryGameScene::update()
{
	switch (storyState)
	{
	// Render update if story is in narration mode
	case StoryGameScene::StoryState::Narration:
		narrationUpdate();
		break;
	// Render update if story is in playing level mode
	case StoryGameScene::StoryState::Level:
		levelUpdate();
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
	case StoryGameScene::StoryState::Narration:
		narrationHandleInput(e);
		break;
	// Handle input if story is in playing level mode
	case StoryGameScene::StoryState::Level:
		levelHandleInput(e);
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
	backgroundTransitionTexture = util::loadTexture(renderer, "Textures/Background/StoryTransition.png");
	if (backgroundTransitionTexture == NULL)
	{
		std::cout << "Failed to load texture image!" << std::endl;
		success = false;
	}

	// Load the font
	font = TTF_OpenFont("UI/Fonts/p5hatty.ttf", util::HEADING_FONT_SIZE);
	if (font == NULL)
	{
		std::cout << "Failed to load font! SDL_Error: " << TTF_GetError() << std::endl;
		success = false;
	}

	// Load media for narration menu
	narrationMenu->loadMedia();

	return success;
}

void StoryGameScene::narrationHandleInput(SDL_Event* e)
{
	narrationMenu->handleInput(e);

	shouldQuit = narrationMenu->hasRequestedQuit() | shouldQuit;
}

void StoryGameScene::levelHandleInput(SDL_Event* e)
{
	// Let level handle it's own input
	currentLevel->handleInput(e);
	// Check if level has ended
	if (currentLevel->hasEnded())
	{
		// Delete the level
		delete currentLevel;
		// Finish the chapter narration
		storyState = StoryState::Narration;
		// Update chapter line
		currentChapterLine = chapters[currentChapterIndex]->getNextLine();
		// Show menu
		narrationMenu->show();
	}
	// Check if level requested to quit the whole game
	if (currentLevel->hasRequestedQuit())
	{
		// Delete the level
		delete currentLevel;
		// Request a quit application
		shouldQuit = true;
	}
	// Check if level requested to go to main menu
	if (currentLevel->hasRequestedMainMenu())
	{
		// Delete the level
		delete currentLevel;
		// Request MainMenu
		nextGameState = GameState::MainMenu;
	}
}

void StoryGameScene::narrationUpdate()
{
	// Render background texture to screen
	SDL_RenderCopy(renderer, backgroundTransitionTexture, NULL, NULL);

	// Draw title
	SDL_Color white = { 250, 250, 250 };
	util::drawText(renderer, font, white, chapters[currentChapterIndex]->getTitle().c_str(), {screenWidth/10.f, screenHeight/10.f}, util::HEADING_FONT_SIZE);

	// Draw text
	util::drawText(renderer, font, white, currentChapterLine.c_str(), {screenWidth/10.f, screenHeight/2.f}, util::PARAGRAPH_FONT_SIZE);

	// Draw confirm button and it's text
	narrationMenu->update();
}

void StoryGameScene::levelUpdate()
{
	// Render the level on a screen
	currentLevel->update();
}

void StoryGameScene::ok()
{
	narrationMenu->reset();

	currentChapterLine = chapters[currentChapterIndex]->getNextLine();
	if (currentChapterLine._Equal("PLAY"))
	{
		// Change state for playing the level
		storyState = StoryState::Level;
		// Initialize the level
		StoryChapter* chapter = chapters[currentChapterIndex];
		currentLevel = new Level(chapter->getPathToLevel(), renderer, player, chapter->getTitle(), true);
		// Load the level media
		if (!currentLevel->loadMedia())
		{
			std::cout << "Failed to load the level media!" << std::endl;
		}
	}
	else if (currentChapterLine._Equal("END"))
	{
		currentChapterIndex += 1;
		if (currentChapterIndex == 3)
		{
			// Finished all of the chapters, return to the MainMenu
			nextGameState = GameState::MainMenu;
		}
		else
		{
			currentChapterLine = chapters[currentChapterIndex]->getNextLine();
			narrationMenu->show();
		}
	}
	else
	{
		narrationMenu->show();
	}
}
