#pragma once
#include "GameScene.h"
class MainMenuGameScene : public GameScene
{
public:

	enum class MainMenuState
	{
		FIRST_MENU,
		SECOND_MENU
	};

	MainMenuGameScene(SDL_Renderer* _renderer) : GameScene(_renderer) 
	{
		// Initialize member variables
		mainMenuState = MainMenuState::FIRST_MENU;
		selectedButtonPosition = PLAY_BUTTON_POSITION;
		previousStateButtonPosition = { -1, -1 };

		// Initialize textures
		backgroundTexture = NULL;
		blackButtonTexture = NULL;
		whiteButtonTexture = NULL;
		orangeButtonTexture = NULL;

		// Initialize font
		font = NULL;
	}
	~MainMenuGameScene()
	{
		// Free loaded images
		SDL_DestroyTexture(backgroundTexture);
		backgroundTexture = NULL;
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
	void update();
	bool handleInput(SDL_Event* e);
	bool loadMedia();
private:
	/// <summary>
	/// Draws button on the screen.
	/// </summary>
	/// <param name="texture">Button texture</param>
	/// <param name="position">Button position on the screen</param>
	void drawButton(SDL_Texture* texture, Position position);
	/// <summary>
	/// Draws a text on the screen.
	/// </summary>
	/// <param name="color">Color of the text</param>
	/// <param name="message">Message of the text</param>
	/// <param name="position">Text position on the screen</param>
	void drawText(SDL_Color color, const char* message, Position position);
	SDL_Color getTextColor(Position buttonPosition);

	const Position PLAY_BUTTON_POSITION = { 100, 250 };
	const Position QUIT_BUTTON_POSITION = { 100, 450 };
	const Position STORY_BUTTON_POSITION = { 550, 250 };
	const Position ARCADE_BUTTON_POSITION = { 550, 370 };
	const Position COOP_BUTTON_POSITION = { 550, 490 };

	const Position PLAY_TEXT_POSITION = { 190, 260 };
	const Position QUIT_TEXT_POSITION = { 190, 465 };
	const Position STORY_TEXT_POSITION = { 620, 270 };
	const Position ARCADE_TEXT_POSITION = { 600, 390 };
	const Position COOP_TEXT_POSITION = { 620, 510 };

	MainMenuState mainMenuState;
	Position selectedButtonPosition;
	Position previousStateButtonPosition;

	SDL_Texture* backgroundTexture;
	SDL_Texture* blackButtonTexture;
	SDL_Texture* whiteButtonTexture;
	SDL_Texture* orangeButtonTexture;

	TTF_Font* font;
};

