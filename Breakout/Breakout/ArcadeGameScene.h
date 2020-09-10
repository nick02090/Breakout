#pragma once
#include "GameScene.h"
class ArcadeGameScene : public GameScene
{
public:

	enum class ArcadeState
	{
	};

	ArcadeGameScene(SDL_Renderer* _renderer);
	~ArcadeGameScene();
	/// <summary>
	/// Updates the screen window.
	/// </summary>
	void update();
	/// <summary>
	/// Handles input.
	/// </summary>
	void handleInput(SDL_Event* e);
	/// <summary>
	/// Loads required media.
	/// </summary>
	bool loadMedia();
private:
};

