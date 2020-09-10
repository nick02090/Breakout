#pragma once
#include "GameObject.h"
class Brick : public GameObject
{
public:
	Brick(SDL_Renderer* _renderer, std::string _name, std::string _ID, std::string _texturePath, int _hitPoints,
		std::string _hitSoundPath, std::string _breakSoundPath, int _breakScore);
	Brick(Brick* _brick);
	Brick(SDL_Renderer* _renderer, std::string _name, std::string _ID);
	~Brick();
	/// <summary>
	/// Renders brick on the screen.
	/// </summary>
	/// <param name="_screenPosition">Screen position that the brick is rendered on</param>
	/// <param name="widthFactor">Width factor that is applied to the width size of the rendered brick texture</param>
	/// <param name="heightFactor">Height factor that is applied to the height size of the rendered brick texture</param>
	void render(util::Position _screenPosition, float widthFactor = 1.0, float heightFactor = 1.0);
	/// <summary>
	/// Updates bricks parameters as if it was hit by a ball and potentially deletes it.
	/// </summary>
	void hit();
	/// <summary>
	/// Determines whether the brick has already been crushed (destroyed).
	/// </summary>
	/// <returns></returns>
	bool getIsCrushed();
	/// <summary>
	/// Determines whether the brick is actually an empty space size of the brick.
	/// </summary>
	/// <returns></returns>
	bool getIsEmpty();
	/// <summary>
	/// Returns score for breaking this brick.
	/// </summary>
	/// <returns></returns>
	int getBreakScore();
	/// <summary>
	/// Returns brick ID.
	/// </summary>
	/// <returns></returns>
	std::string getId();
	/// <summary>
	/// Determines whether the brick is breakable (can be crushed) or not.
	/// </summary>
	/// <returns></returns>
	bool isBreakable();
	/// <summary>
	/// Resets bricks parameters as it was just created.
	/// </summary>
	void reset();
private:
	const float Width = 50.f;
	const float Height = 20.f;

	std::string name;
	std::string id;
	std::string hitSoundPath;
	std::string breakSoundPath;
	std::string texturePath;
	/// <summary>
	/// Number of the hits necessary to destroy the brick
	/// </summary>
	int hitPoints;
	/// <summary>
	/// Score reward that is given to player when the brick is crushed
	/// </summary>
	int breakScore;
	/// <summary>
	/// Number of times hit
	/// </summary>
	int timesHit;
	/// <summary>
	/// True if it is crushed down (destroyed)
	/// </summary>
	bool isCrushed = false;
	/// <summary>
	/// True if it represents an empty space on the screen and shouldn't be rendered or used in any way
	/// </summary>
	bool isEmpty = false;

	SDL_Texture* texture;
};
