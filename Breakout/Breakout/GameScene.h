#pragma once
#include <SDL.h>
#include <SDL_image.h>
class GameScene
{
public:
	GameScene(SDL_Renderer* _renderer) : renderer(_renderer) {}
	~GameScene() {}
	/// <summary>
	/// Updates the screen window.
	/// </summary>
	virtual void update() = 0;
	/// <summary>
	/// Handles input.
	/// </summary>
	virtual bool handleInput(SDL_Event* e) = 0;
	/// <summary>
	/// Loads required media.
	/// </summary>
	virtual bool loadMedia() = 0;
protected:
	SDL_Renderer* renderer;
};

