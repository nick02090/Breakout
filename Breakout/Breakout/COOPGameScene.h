#pragma once
#include "GameScene.h"
class COOPGameScene : public GameScene
{
public:

	enum class COOPState
	{
	};

	COOPGameScene(SDL_Renderer* _renderer);
	~COOPGameScene();
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
};

