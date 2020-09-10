#include "Menu.h"

Menu::Menu(std::vector<MenuButton> _buttons, SDL_Renderer* _renderer) : buttons(_buttons), renderer(_renderer)
{
	// Calculate number of elements
	numberOfElements = buttons.size();

	// Initialize member variables
	init();

	// Initialize textures
	blackButtonTexture = NULL;
	whiteButtonTexture = NULL;
	orangeButtonTexture = NULL;

	// Initialize font
	font = NULL;
}

Menu::~Menu()
{
	// Free loaded images
	SDL_DestroyTexture(blackButtonTexture);
	blackButtonTexture = NULL;
	SDL_DestroyTexture(whiteButtonTexture);
	whiteButtonTexture = NULL;
	SDL_DestroyTexture(orangeButtonTexture);
	orangeButtonTexture = NULL;

	// Free loaded font
	TTF_CloseFont(font);
	font = NULL;
}

void Menu::update()
{
	if (isVisible)
	{
		// Render buttons on the screen
		for (const auto& button : buttons)
		{
			util::drawButton(renderer, blackButtonTexture, button.buttonPosition);
		}

		// Add extra layer to the selected button
		util::drawButton(renderer, whiteButtonTexture, buttons[currentElementIndex].buttonPosition);

		// Add extra layer to previous state selected button if there is one
		if (requestedElementIndex >= 0)
		{
			util::drawButton(renderer, orangeButtonTexture, buttons[requestedElementIndex].buttonPosition);
		}

		// Add text to buttons
		for (const auto& button : buttons)
		{
			util::drawText(renderer, font, getTextColor(button.buttonPosition), button.text, button.textPosition, util::HEADING_FONT_SIZE);
		}
	}
}

void Menu::loadMedia()
{
	// Load black button background
	blackButtonTexture = util::loadTexture(renderer, "UI/Textures/Buttons/BlackButton.png");
	if (blackButtonTexture == NULL)
	{
		std::cout << "Failed to load texture image!" << std::endl;
	}

	// Load white button background
	whiteButtonTexture = util::loadTexture(renderer, "UI/Textures/Buttons/WhiteButton.png");
	if (whiteButtonTexture == NULL)
	{
		std::cout << "Failed to load texture image!" << std::endl;
	}

	// Load orange button background
	orangeButtonTexture = util::loadTexture(renderer, "UI/Textures/Buttons/OrangeButton.png");
	if (orangeButtonTexture == NULL)
	{
		std::cout << "Failed to load texture image!" << std::endl;
	}

	// Load the font
	font = TTF_OpenFont("UI/Fonts/p5hatty.ttf", util::HEADING_FONT_SIZE);
	if (font == NULL)
	{
		std::cout << "Failed to load font! SDL_Error: " << TTF_GetError() << std::endl;
	}
}

void Menu::handleInput(SDL_Event* e)
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
				setPrevious();
				break;
				// Down arrow key
			case SDLK_DOWN:
				setNext();
				break;
				// Enter key
			case SDLK_RETURN:
				requestedElementIndex = currentElementIndex;
				break;
				// Backspace key
			case SDLK_BACKSPACE:
				shouldReverse = true;
				break;
			default:
				break;
			}
		}
	}
}

void Menu::hide()
{
	isVisible = false;
}

void Menu::show()
{
	isVisible = true;
}

bool Menu::hasRequestedQuit()
{
	return shouldQuit;
}

int Menu::confirmSelection()
{
	return requestedElementIndex;
}

bool Menu::hasRequestedReverse()
{
	return shouldReverse;
}

void Menu::init()
{
	currentElementIndex = 0;
	requestedElementIndex = -1;
	shouldQuit = false;
	shouldReverse = false;
	isVisible = false;
}

void Menu::reset()
{
	init();
}

void Menu::setNext() {
	currentElementIndex = util::clamp(currentElementIndex + 1, 0, numberOfElements - 1);
}

void Menu::setPrevious() {
	currentElementIndex = util::clamp(currentElementIndex - 1, 0, numberOfElements - 1);
}

int Menu::getCurrent()
{
	return currentElementIndex;
}

SDL_Color Menu::getTextColor(util::Position buttonPosition)
{
	util::Position selectedButtonPosition = buttons[currentElementIndex].buttonPosition;
	util::Position previousStateButtonPosition = buttons[currentElementIndex].buttonPosition;

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