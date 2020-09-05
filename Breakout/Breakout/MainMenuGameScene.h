#pragma once
#include "GameScene.h"
class MainMenuGameScene : public GameScene
{
public:
	MainMenuGameScene(SDL_Renderer* _renderer) : GameScene(_renderer) 
	{
		texture = NULL;
	}
	~MainMenuGameScene()
	{
		// Free loaded image
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
	void update();
	bool handleInput(SDL_Event* e);
	bool loadMedia();
private:
	SDL_Texture* texture;
};

