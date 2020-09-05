#pragma once
#include "GameScene.h"
class StoryGameScene : public GameScene
{
public:

	enum class StoryState
	{
		FIRST_CHAPTER,
		SECOND_CHAPTER,
		THIRD_CHAPTER
	};

	StoryGameScene(SDL_Renderer* _renderer) : GameScene(_renderer)
	{

	}
	~StoryGameScene()
	{

	}
	void update();
	void handleInput(SDL_Event* e);
	bool loadMedia();
private:
};

