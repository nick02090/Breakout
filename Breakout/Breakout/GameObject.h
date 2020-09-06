#pragma once
#include "Utilities.h"
class GameObject
{
public:

	enum class GameObjectType
	{
		Circle,
		Rectangle
	};

	GameObject(SDL_Renderer* _renderer) : renderer(_renderer) {}

	/// <summary>
	/// Renders an object on the screen by creating a copy of the object.
	/// </summary>
	/// <param name="screenPosition">Position on the screen that object is placed to</param>
	/// <param name="widthFactor">Width scaling factor that scales down objects width</param>
	/// <param name="heightFactor">Height scaling factor that scales down objects height</param>
	virtual void render(util::Position screenPosition, float widthFactor = 1.0, float heightFactor = 1.0) = 0;
	/// <summary>
	/// Determines whether the object is colliding with an other object.
	/// </summary>
	/// <param name="otherObject">The other object</param>
	/// <returns></returns>
	bool isInCollisionWith(GameObject* otherObject)
	{
		// TODO: Implement collision check based on objects type and position
	}
	/// <summary>
	/// Type of the game object. This is used for collision checking.
	/// </summary>
	GameObjectType type;
	/// <summary>
	/// Objects position on the screen.
	/// </summary>
	util::Position screenPosition;
	/// <summary>
	/// Renderer for rendering the object on the screen.
	/// </summary>
	SDL_Renderer* renderer;
};

