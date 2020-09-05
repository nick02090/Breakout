#pragma once
#include "GameScene.h"
class ArcadeGameScene : public GameScene
{
public:

	enum class ArcadeState
	{
	};

	ArcadeGameScene(SDL_Renderer* _renderer) : GameScene(_renderer)
	{

	}
	~ArcadeGameScene()
	{

	}
	void update();
	void handleInput(SDL_Event* e);
	bool loadMedia();
private:
};

