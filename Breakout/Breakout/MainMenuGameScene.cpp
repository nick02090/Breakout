#include "MainMenuGameScene.h"

void MainMenuGameScene::update()
{
	// Render background texture to screen
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	// Render UI to screen
	switch (mainMenuState)
	{
	case MainMenuGameScene::MainMenuState::FIRST_MENU:
		// Draw PLAY button
		util::drawButton(renderer, blackButtonTexture, PLAY_BUTTON_POSITION);
		// Draw QUIT button
		util::drawButton(renderer, blackButtonTexture, QUIT_BUTTON_POSITION);
		break;
	case MainMenuGameScene::MainMenuState::SECOND_MENU:
		// Draw PLAY button
		util::drawButton(renderer, blackButtonTexture, PLAY_BUTTON_POSITION);
		// Draw QUIT button
		util::drawButton(renderer, blackButtonTexture, QUIT_BUTTON_POSITION);
		// Draw STORY button
		util::drawButton(renderer, blackButtonTexture, STORY_BUTTON_POSITION);
		// Draw ARCADE button
		util::drawButton(renderer, blackButtonTexture, ARCADE_BUTTON_POSITION);
		// Draw CO-OP button
		util::drawButton(renderer, blackButtonTexture, COOP_BUTTON_POSITION);
		break;
	default:
		std::cout << "Invalid MainMenuState!" << std::endl;
		break;
	}

	// Add extra layer to selected button
	util::drawButton(renderer, whiteButtonTexture, buttonPositions[selectedButtonIndex]);

	// Add extra layer to previous state selected button if there is one
	if (previousStateButtonIndex >= 0)
	{
		util::drawButton(renderer, orangeButtonTexture, buttonPositions[previousStateButtonIndex]);
	}

	// Add text to buttons
	switch (mainMenuState)
	{
	case MainMenuGameScene::MainMenuState::FIRST_MENU:
		// Draw PLAY text
		util::drawText(renderer, font, getTextColor(PLAY_BUTTON_POSITION), "PLAY", PLAY_TEXT_POSITION, util::HEADING_FONT_SIZE);
		// Draw QUIT text
		util::drawText(renderer, font, getTextColor(QUIT_BUTTON_POSITION), "QUIT", QUIT_TEXT_POSITION, util::HEADING_FONT_SIZE);
		break;
	case MainMenuGameScene::MainMenuState::SECOND_MENU:
		// Draw PLAY text
		util::drawText(renderer, font, getTextColor(PLAY_BUTTON_POSITION), "PLAY", PLAY_TEXT_POSITION, util::HEADING_FONT_SIZE);
		// Draw QUIT text
		util::drawText(renderer, font, getTextColor(QUIT_BUTTON_POSITION), "QUIT", QUIT_TEXT_POSITION, util::HEADING_FONT_SIZE);
		// Draw STORY text
		util::drawText(renderer, font, getTextColor(STORY_BUTTON_POSITION), "STORY", STORY_TEXT_POSITION, util::HEADING_FONT_SIZE);
		// Draw ARCADE text
		util::drawText(renderer, font, getTextColor(ARCADE_BUTTON_POSITION), "ARCADE", ARCADE_TEXT_POSITION, util::HEADING_FONT_SIZE);
		// Draw CO-OP text
		util::drawText(renderer, font, getTextColor(COOP_BUTTON_POSITION), "CO-OP", COOP_TEXT_POSITION, util::HEADING_FONT_SIZE);
		break;
	default:
		std::cout << "Invalid MainMenuState!" << std::endl;
		break;
	}
}

void MainMenuGameScene::handleInput(SDL_Event* e)
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
			// Up arrow key
			case SDLK_UP:
				updateCurrentButton(-1);
				break;
			// Down arrow key
			case SDLK_DOWN:
				updateCurrentButton(1);
				break;
			// Enter key
			case SDLK_RETURN:
				updateCurrentState();
				break;
			// Backspace key
			case SDLK_BACKSPACE:
				mainMenuState = MainMenuState::FIRST_MENU;
				selectedButtonIndex = 0;
				previousStateButtonIndex = -1;
				break;
			default:
				break;
			}
		}
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

	// Load black button background
	blackButtonTexture = util::loadTexture(renderer, "UI/Textures/Buttons/BlackButton.png");
	if (blackButtonTexture == NULL)
	{
		std::cout << "Failed to load texture image!" << std::endl;
		success = false;
	}

	// Load white button background
	whiteButtonTexture = util::loadTexture(renderer, "UI/Textures/Buttons/WhiteButton.png");
	if (whiteButtonTexture == NULL)
	{
		std::cout << "Failed to load texture image!" << std::endl;
		success = false;
	}

	// Load orange button background
	orangeButtonTexture = util::loadTexture(renderer, "UI/Textures/Buttons/OrangeButton.png");
	if (orangeButtonTexture == NULL)
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

	return success;
}

SDL_Color MainMenuGameScene::getTextColor(util::Position buttonPosition)
{
	util::Position selectedButtonPosition = buttonPositions[selectedButtonIndex];
	util::Position previousStateButtonPosition = buttonPositions[previousStateButtonIndex];

	// If the button position is the same as the currently selected button position return black color
	if (selectedButtonPosition.x == buttonPosition.x && selectedButtonPosition.y == buttonPosition.y)
	{
		SDL_Color blackColor = { 0, 0, 0 };
		return blackColor;
	}
	// If the previous state selected button position is the same as the given position return black color
	else if (previousStateButtonPosition.x == buttonPosition.x && previousStateButtonPosition.y == buttonPosition.y)
	{
		SDL_Color blackColor = { 0, 0, 0 };
		return blackColor;
	}
	else
	{
		SDL_Color whiteColor = { 250, 250, 250 };
		return whiteColor;
	}
}

void MainMenuGameScene::updateCurrentButton(int offset)
{
	switch (mainMenuState)
	{
	case MainMenuGameScene::MainMenuState::FIRST_MENU:
		// Clamp the selected button index to indexes of a first menu state
		selectedButtonIndex = util::clamp(selectedButtonIndex + offset, 0, 1);
		break;
	case MainMenuGameScene::MainMenuState::SECOND_MENU:
		// Clamp the selected button index to indexes of a second menu state
		selectedButtonIndex = util::clamp(selectedButtonIndex + offset, 2, 4);
		break;
	default:
		std::cout << "Invalid MainMenuState!" << std::endl;
		break;
	}
}

void MainMenuGameScene::updateCurrentState()
{
	switch (mainMenuState)
	{
	case MainMenuGameScene::MainMenuState::FIRST_MENU:
		// User selected to play the game
		if (selectedButtonIndex == 0)
		{
			previousStateButtonIndex = 0;
			selectedButtonIndex = 2;
			mainMenuState = MainMenuState::SECOND_MENU;
		}
		// User selected to quit the game
		else if (selectedButtonIndex == 1)
		{
			shouldQuit = true;
		}
		break;
	case MainMenuGameScene::MainMenuState::SECOND_MENU:
		// User selected to play the STORY mode
		if (selectedButtonIndex == 2)
		{
			nextGameState = GameState::STORY;
		}
		// User selected to play the ARCADE mode
		else if (selectedButtonIndex == 3)
		{
			nextGameState = GameState::ARCADE;
		}
		// User selected to play the CO-OP mode
		else if (selectedButtonIndex == 4)
		{
			nextGameState = GameState::COOP;
		}
		break;
	default:
		std::cout << "Invalid MainMenuState!" << std::endl;
		break;
	}
}
