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
		previousStateButtonIndex = -1;
		selectedButtonIndex = 0;

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
	void handleInput(SDL_Event* e);
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
	/// <summary>
	/// Gets color for the text based on the button that is placed on.
	/// </summary>
	/// <param name="buttonPosition">Position of the button that text is placed on</param>
	/// <returns></returns>
	SDL_Color getTextColor(Position buttonPosition);
	/// <summary>
	/// Update current selected button by increasing/decreasing the index by the offset.
	/// </summary>
	/// <param name="offset">Offset by which is the index updated</param>
	void updateCurrentButton(int offset);
	/// <summary>
	/// Updates current MainMenu state.
	/// </summary>
	void updateCurrentState();

	const Position PLAY_BUTTON_POSITION = { 110, 250 };
	const Position QUIT_BUTTON_POSITION = { 110, 450 };
	const Position STORY_BUTTON_POSITION = { 550, 250 };
	const Position ARCADE_BUTTON_POSITION = { 550, 370 };
	const Position COOP_BUTTON_POSITION = { 550, 490 };

	const Position PLAY_TEXT_POSITION = { 190, 260 };
	const Position QUIT_TEXT_POSITION = { 190, 465 };
	const Position STORY_TEXT_POSITION = { 620, 270 };
	const Position ARCADE_TEXT_POSITION = { 600, 390 };
	const Position COOP_TEXT_POSITION = { 620, 510 };

	MainMenuState mainMenuState;
	int previousStateButtonIndex;
	int selectedButtonIndex;
	Position buttonPositions[5] = {PLAY_BUTTON_POSITION, QUIT_BUTTON_POSITION, STORY_BUTTON_POSITION, 
		ARCADE_BUTTON_POSITION, COOP_BUTTON_POSITION};

	SDL_Texture* backgroundTexture;
	SDL_Texture* blackButtonTexture;
	SDL_Texture* whiteButtonTexture;
	SDL_Texture* orangeButtonTexture;

	TTF_Font* font;
};

