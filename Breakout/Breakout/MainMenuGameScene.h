#pragma once
#include "GameScene.h"
class MainMenuGameScene : public GameScene
{
public:
	MainMenuGameScene(SDL_Renderer* _renderer) : GameScene(_renderer) 
	{
		// Initialize member variables
		firstMenu = new Menu(firstMenuButtons, renderer);
		secondMenu = new Menu(secondMenuButtons, renderer);
		currentMenu = firstMenu;
		currentMenuRequests = firstMenuRequests;
		currentMenu->show();

		// Initialize textures
		backgroundTexture = NULL;
	}
	~MainMenuGameScene()
	{
		// Free loaded images
		SDL_DestroyTexture(backgroundTexture);
		backgroundTexture = NULL;
	}
	void update();
	void handleInput(SDL_Event* e);
	bool loadMedia();
private:
	void play();
	void quit();
	void story();
	void arcade();
	void coop();

	const util::Position PLAY_BUTTON_POSITION = { 110.f, 250.f };
	const util::Position QUIT_BUTTON_POSITION = { 110.f, 450.f };
	const util::Position STORY_BUTTON_POSITION = { 550.f, 250.f };
	const util::Position ARCADE_BUTTON_POSITION = { 550.f, 370.f };
	const util::Position COOP_BUTTON_POSITION = { 550.f, 490.f };

	const util::Position PLAY_TEXT_POSITION = { 190.f, 260.f };
	const util::Position QUIT_TEXT_POSITION = { 190.f, 465.f };
	const util::Position STORY_TEXT_POSITION = { 620.f, 270.f };
	const util::Position ARCADE_TEXT_POSITION = { 600.f, 390.f };
	const util::Position COOP_TEXT_POSITION = { 620.f, 510.f };

	Menu* currentMenu;
	Menu* firstMenu;
	Menu* secondMenu;
	std::vector<MenuButton> firstMenuButtons{ 
		{ PLAY_BUTTON_POSITION, PLAY_TEXT_POSITION, "PLAY" }, 
		{ QUIT_BUTTON_POSITION, QUIT_TEXT_POSITION, "QUIT" } 
	};
	std::vector<MenuButton> secondMenuButtons{ 
		{ STORY_BUTTON_POSITION, STORY_TEXT_POSITION, "STORY" }, 
		{ ARCADE_BUTTON_POSITION, ARCADE_TEXT_POSITION, "ARCADE" }, 
		{ COOP_BUTTON_POSITION, COOP_TEXT_POSITION, "COOP" } 
	};
	
	typedef void (MainMenuGameScene::*menuRequest)(void);
	menuRequest firstMenuRequests[2] = { &MainMenuGameScene::play, &MainMenuGameScene::quit };
	menuRequest secondMenuRequests[3] = { &MainMenuGameScene::story, &MainMenuGameScene::arcade, &MainMenuGameScene::coop};
	menuRequest* currentMenuRequests;

	SDL_Texture* backgroundTexture;
};

