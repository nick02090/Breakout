#pragma once
#include "Utilities.h"
struct MenuButton {
	util::Position buttonPosition;
	util::Position textPosition;
	const char* text;
};

template<typename T>
class Menu
{
public:

	typedef void (T::* MenuRequest)(void);

	Menu(std::vector<MenuButton> _buttons, SDL_Renderer* _renderer, MenuRequest* _menuRequests, T* _menuCaller) 
		: buttons(_buttons), renderer(_renderer), menuRequests(_menuRequests), menuCaller(_menuCaller)
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
	~Menu()
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
	/// <summary>
	/// Updates the screen window.
	/// </summary>
	void update(float deltaTime)
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
				util::drawText(renderer, font, getTextColor(button.buttonPosition), button.text, button.textPosition, util::HeadingFontSize);
			}
		}
	}
	/// <summary>
	/// Loads required media.
	/// </summary>
	void loadMedia()
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
		font = TTF_OpenFont("UI/Fonts/p5hatty.ttf", util::HeadingFontSize);
		if (font == NULL)
		{
			std::cout << "Failed to load font! SDL_Error: " << TTF_GetError() << std::endl;
		}
	}
	/// <summary>
	/// Handles input.
	/// </summary>
	/// <param name="e"></param>
	void handleInput(SDL_Event* e)
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
					(menuCaller->*menuRequests[requestedElementIndex])();
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
	/// <summary>
	/// Doesn't render the menu on the screen until told otherwise.
	/// </summary>
	void hide()
	{
		isVisible = false;
	}
	/// <summary>
	/// Renders menu on the screen the next frame.
	/// </summary>
	void show()
	{
		isVisible = true;
	}
	/// <summary>
	/// Determines whether the user has requested to quit an application.
	/// </summary>
	/// <returns></returns>
	bool hasRequestedQuit()
	{
		return shouldQuit;
	}
	/// <summary>
	/// Determines whether the menu should go back to previous menu.
	/// </summary>
	/// <returns></returns>
	bool hasRequestedReverse()
	{
		return shouldReverse;
	}
	/// <summary>
	/// Sets initial menu parameter values.
	/// </summary>
	void init()
	{
		currentElementIndex = 0;
		requestedElementIndex = -1;
		shouldQuit = false;
		shouldReverse = false;
		isVisible = false;
	}
	/// <summary>
	/// Resets the menu at its initial state.
	/// </summary>
	void reset()
	{
		init();
	}
private:
	/// <summary>
	/// Sets the next button in the list as the selected one.
	/// </summary>
	void setNext()
	{
		currentElementIndex = util::clamp(currentElementIndex + 1, 0, numberOfElements - 1);
	}
	/// <summary>
	/// Sets the previous button in the list as the selected one.
	/// </summary>
	void setPrevious()
	{
		currentElementIndex = util::clamp(currentElementIndex - 1, 0, numberOfElements - 1);
	}
	/// <summary>
	/// Returns the index of a currently selected button.
	/// </summary>
	int getCurrent()
	{
		return currentElementIndex;
	}
	/// <summary>
	/// Gets color for the text based on the button that is placed on.
	/// </summary>
	/// <param name="buttonPosition">Position of the button that text is placed on</param>
	/// <returns></returns>
	SDL_Color getTextColor(util::Position buttonPosition)
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

	int numberOfElements;
	std::vector<MenuButton> buttons;
	int currentElementIndex;
	int requestedElementIndex;
	bool shouldQuit;
	bool shouldReverse;
	bool isVisible;

	SDL_Renderer* renderer;
	TTF_Font* font;
	SDL_Texture* blackButtonTexture;
	SDL_Texture* whiteButtonTexture;
	SDL_Texture* orangeButtonTexture;

	MenuRequest* menuRequests;
	T* menuCaller;
};

