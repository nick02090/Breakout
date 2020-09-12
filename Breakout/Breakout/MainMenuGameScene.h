#pragma once
#include "GameScene.h"
class MainMenuGameScene : public GameScene
{
public:
	MainMenuGameScene(SDL_Renderer* _renderer);
	~MainMenuGameScene();
	/// <summary>
	/// Updates the screen window.
	/// </summary>
	void update(float deltaTime);
	/// <summary>
	/// Handles input.
	/// </summary>
	void handleInput(SDL_Event* e);
	/// <summary>
	/// Loads required media.
	/// </summary>
	bool loadMedia();
private:
	/// <summary>
	/// Selected PLAY button on the menu.
	/// </summary>
	void play();
	/// <summary>
	/// Selected QUIT button on the menu.
	/// </summary>
	void quit();
	/// <summary>
	/// Selected STORY button on the menu.
	/// </summary>
	void story();
	/// <summary>
	/// Selected ARCADE button on the menu.
	/// </summary>
	void arcade();
	/// <summary>
	/// Selected COOP button on the menu.
	/// </summary>
	void coop();

	const util::Position PlayButtonPosition = { 110.f, 250.f };
	const util::Position QuitButtonPosition = { 110.f, 450.f };
	const util::Position StoryButtonPosition = { 550.f, 250.f };
	const util::Position ArcadeButtonPosition = { 550.f, 370.f };
	const util::Position CoopButtonPosition = { 550.f, 490.f };

	const util::Position PlayTextPosition = { 190.f, 260.f };
	const util::Position QuitTextPosition = { 190.f, 465.f };
	const util::Position StoryTextPosition = { 620.f, 270.f };
	const util::Position ArcadeTextPosition = { 600.f, 390.f };
	const util::Position CoopTextPosition = { 620.f, 510.f };

	Menu<MainMenuGameScene>* currentMenu;
	Menu<MainMenuGameScene>* firstMenu;
	Menu<MainMenuGameScene>* secondMenu;
	std::vector<MenuButton> firstMenuButtons{ 
		{ PlayButtonPosition, PlayTextPosition, "PLAY" }, 
		{ QuitButtonPosition, QuitTextPosition, "QUIT" } 
	};
	std::vector<MenuButton> secondMenuButtons{ 
		{ StoryButtonPosition, StoryTextPosition, "STORY" }, 
		{ ArcadeButtonPosition, ArcadeTextPosition, "ARCADE" }, 
		{ CoopButtonPosition, CoopTextPosition, "COOP" } 
	};
	
	//typedef void (MainMenuGameScene::*menuRequest)(void);
	Menu<MainMenuGameScene>::MenuRequest firstMenuRequests[2] = { &MainMenuGameScene::play, &MainMenuGameScene::quit };
	Menu<MainMenuGameScene>::MenuRequest secondMenuRequests[3] = { &MainMenuGameScene::story, &MainMenuGameScene::arcade, &MainMenuGameScene::coop};
	Menu<MainMenuGameScene>::MenuRequest* currentMenuRequests;

	SDL_Texture* backgroundTexture;
	Mix_Music* backgroundMusic;
};

