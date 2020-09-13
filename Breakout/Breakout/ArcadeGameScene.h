#pragma once
#include "GameScene.h"
#include "LevelGenerator.h"
class ArcadeGameScene : public GameScene
{
public:
	ArcadeGameScene(SDL_Renderer* _renderer);
	~ArcadeGameScene();
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
	Player* player;
	LevelGenerator* levelGenerator;
	Level* level;
	util::SaveData saveData;
};

