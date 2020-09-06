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
	~Brick()
	{
		// Free loaded images
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
	void render(util::Position screenPosition)
	{

	}
	/// <summary>
	/// Updates bricks parameters and potentially deletes it.
	/// </summary>
	inline void hit()
	{
		timesHit += 1;
		if (timesHit == hitPoints)
		{
			// TODO: should delete
		}
	}
	/// <summary>
	/// Returns score for breaking this brick.
	/// </summary>
	/// <returns></returns>
	inline int getBreakScore()
	{
		return breakScore;
	}
private:
	std::string name;
	std::string ID;
	std::string texturePath;
	int hitPoints;
	std::string hitSoundPath;
	std::string breakSoundPath;
	int breakScore;

	/// <summary>
	/// Number of times hit
	/// </summary>
	int timesHit;

	SDL_Texture* texture;
};

