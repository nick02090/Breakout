#pragma once
#include "GameObject.h"
class Ball : public GameObject
{
public:

	enum class WallHit {
		VERTICAL,
		HORIZIONTAL
	};

	Ball(SDL_Renderer* _renderer) : GameObject(_renderer) 
	{
		// Set object type
		type = GameObjectType::Circle;
		// Load all necessary assets
		texture = util::loadTexture(renderer, TEXTURE_PATH);

		previousWall = WallHit::VERTICAL;

		width = WIDTH;
		height = HEIGHT;
		radius = 10.f;
	}
	~Ball()
	{
		// Free loaded images
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
	void render(util::Position _screenPosition, float widthFactor = 1.0, float heightFactor = 1.0)
	{
		// Update position on the screen
		screenPosition = _screenPosition;

		// Create a rect to position the texture
		SDL_FRect rect;
		rect.x = util::clamp(screenPosition.x, 0.f, 1024.f - 20.f);
		rect.y = util::clamp(screenPosition.y, 0.f, 768.f - 105.f);
		rect.w = width / widthFactor;
		rect.h = height / heightFactor;

		// Render the texture on the screen
		SDL_RenderCopyF(renderer, texture, NULL, &rect);
	}
	inline bool hasHitWall()
	{
		if (screenPosition.x == 0.f || screenPosition.x == 1024.f - 20.f)
		{
			previousWall = WallHit::HORIZIONTAL;
			return true;
		}
		if (screenPosition.y == 0.f)
		{
			previousWall = WallHit::VERTICAL;
			return true;
		}
		return false;
	}
	inline WallHit getPreviousWallHit()
	{
		return previousWall;
	}
	inline bool hasFellDown()
	{
		if (screenPosition.y >= 768.f - 105.f)
		{
			return true;
		}
		return false;
	}
	inline float getVelocity()
	{
		return 0.07f;
	}
private:
	const std::string TEXTURE_PATH = "GameObjects/Ball.png";

	const float WIDTH = 20.f;
	const float HEIGHT = 20.f;

	WallHit previousWall;

	SDL_Texture* texture;
};

