#pragma once
#include "Utilities.h"
struct MenuButton {
	util::Position buttonPosition;
	util::Position textPosition;
	const char* text;
};

class Menu
{
public:
	Menu(std::vector<MenuButton> _buttons, SDL_Renderer* _renderer);
	~Menu();
	/// <summary>
	/// Updates the screen window.
	/// </summary>
	void update();
	/// <summary>
	/// Loads required media.
	/// </summary>
	void loadMedia();
	/// <summary>
	/// Handles input.
	/// </summary>
	/// <param name="e"></param>
	void handleInput(SDL_Event* e);
	/// <summary>
	/// Doesn't render the menu on the screen until told otherwise.
	/// </summary>
	void hide();
	/// <summary>
	/// Renders menu on the screen the next frame.
	/// </summary>
	void show();
	/// <summary>
	/// Determines whether the user has requested to quit an application.
	/// </summary>
	/// <returns></returns>
	bool hasRequestedQuit();
	/// <summary>
	/// Returns index of a button that was selected or -1 if non was.
	/// </summary>
	/// <returns></returns>
	int confirmSelection();
	/// <summary>
	/// Determines whether the menu should go back to previous menu.
	/// </summary>
	/// <returns></returns>
	bool hasRequestedReverse();
	/// <summary>
	/// Sets initial menu parameter values.
	/// </summary>
	void init();
	/// <summary>
	/// Resets the menu at its initial state.
	/// </summary>
	void reset();
private:
	/// <summary>
	/// Sets the next button in the list as the selected one.
	/// </summary>
	void setNext();
	/// <summary>
	/// Sets the previous button in the list as the selected one.
	/// </summary>
	void setPrevious();
	/// <summary>
	/// Returns the index of a currently selected button.
	/// </summary>
	int getCurrent();
	/// <summary>
	/// Gets color for the text based on the button that is placed on.
	/// </summary>
	/// <param name="buttonPosition">Position of the button that text is placed on</param>
	/// <returns></returns>
	SDL_Color getTextColor(util::Position buttonPosition);

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
};

