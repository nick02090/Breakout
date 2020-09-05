#pragma once
#include "GameScene.h"
class COOPGameScene : public GameScene
{
public:

	enum class COOPState
	{
	};

	COOPGameScene(SDL_Renderer* _renderer) : GameScene(_renderer)
	{

	}
	~COOPGameScene()
	{

	}
	void update();
	void handleInput(SDL_Event* e);
	bool loadMedia();
private:
};

