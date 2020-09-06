#pragma once
#include "GameObject.h"
class Ball : public GameObject
{
public:
	Ball(SDL_Renderer* _renderer) : GameObject(_renderer) 
	{
		// Set object type
		type = GameObjectType::Circle;
		// Load all necessary assets
		texture = util::loadTexture(renderer, TEXTURE_PATH);
	}
	~Ball()
	{
		// Free loaded images
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
	void render(util::Position screenPosition, float widthFactor = 1.0, float heightFactor = 1.0)
	{
		// Create a rect to position the texture
		SDL_Rect rect;
		rect.x = screenPosition.x;
		rect.y = screenPosition.y;
		rect.w = static_cast<int>(WIDTH / widthFactor);
		rect.h = static_cast<int>(HEIGHT / heightFactor);

		// Render the texture on the screen
		SDL_RenderCopy(renderer, texture, NULL, &rect);
	}
private:
	const std::string TEXTURE_PATH = "GameObjects/Ball.png";

	const int WIDTH = 20;
	const int HEIGHT = 20;

	SDL_Texture* texture;
};

