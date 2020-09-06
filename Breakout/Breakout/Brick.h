#pragma once
#include "GameObject.h"
class Brick : public GameObject
{
public:
	Brick(SDL_Renderer* _renderer, std::string _name, std::string _ID, std::string _texturePath, int _hitPoints, 
		std::string _hitSoundPath, std::string _breakSoundPath, int _breakScore) : GameObject(_renderer), name(_name), ID(_ID), texturePath(_texturePath),
		hitPoints(_hitPoints), hitSoundPath(_hitSoundPath), breakSoundPath(_breakSoundPath), breakScore(_breakScore) 
	{
		// Set type of an object
		type = GameObjectType::Rectangle;
		// Initialize member variables
		timesHit = 0;
		// Load all necessary assets
		texture = util::loadTexture(renderer, texturePath);
	}
	Brick(Brick* _brick) : Brick(_brick->renderer, _brick->name, _brick->ID, _brick->texturePath, _brick->hitPoints, _brick->hitSoundPath, _brick->breakSoundPath, _brick->breakScore) {}
	~Brick()
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
	/// <summary>
	/// Updates bricks parameters and potentially deletes it.
	/// </summary>
	inline void hit()
	{
		timesHit += 1;
		if (timesHit == hitPoints)
		{
			isCrushed = true;
		}
	}
	inline bool getIsCrushed()
	{
		return isCrushed;
	}
	/// <summary>
	/// Returns score for breaking this brick.
	/// </summary>
	/// <returns></returns>
	inline int getBreakScore()
	{
		return breakScore;
	}
	/// <summary>
	/// Returns brick ID.
	/// </summary>
	/// <returns></returns>
	inline std::string getID()
	{
		return ID;
	}
private:
	std::string name;
	std::string ID;
	std::string texturePath;
	int hitPoints;
	std::string hitSoundPath;
	std::string breakSoundPath;
	int breakScore;

	const int WIDTH = 50;
	const int HEIGHT = 20;

	/// <summary>
	/// Number of times hit
	/// </summary>
	int timesHit;
	/// <summary>
	/// True if it is crushed down
	/// </summary>
	bool isCrushed = false;

	SDL_Texture* texture;
};
