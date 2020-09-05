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
		mainMenuState = MainMenuState::FIRST_MENU;
		selectedButtonPosition = PLAY_BUTTON_POSITION;
		previousStateButtonPosition = { -1, -1 };

		backgroundTexture = NULL;
		blackButtonTexture = NULL;
		whiteButtonTexture = NULL;
		orangeButtonTexture = NULL;
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

	const Position PLAY_BUTTON_POSITION = { 100, 250 };
	const Position QUIT_BUTTON_POSITION = { 100, 450 };
	const Position STORY_BUTTON_POSITION = { 550, 250 };
	const Position ARCADE_BUTTON_POSITION = { 550, 370 };
	const Position COOP_BUTTON_POSITION = { 550, 490 };

	MainMenuState mainMenuState;
	Position selectedButtonPosition;
	Position previousStateButtonPosition;

	SDL_Texture* backgroundTexture;
	SDL_Texture* blackButtonTexture;
	SDL_Texture* whiteButtonTexture;
	SDL_Texture* orangeButtonTexture;
};

