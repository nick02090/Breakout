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
		// Rectangle - Rectangle collision check
		if (type == GameObjectType::Rectangle && otherObject->type == GameObjectType::Rectangle)
		{
			std::cout << "REC-REC" << std::endl;
		}
		// Circle - Circle collision check
		else if (type == GameObjectType::Circle && otherObject->type == GameObjectType::Circle)
		{
			std::cout << "CIR-CIR" << std::endl;
		}
		// Circle - Rectangle collision check
		else if (type == GameObjectType::Circle && otherObject->type == GameObjectType::Rectangle)
		{
			return circleToRectangleCollision(this, otherObject);
		}
		// Rectangle - Circle check
		else if (type == GameObjectType::Rectangle && otherObject->type == GameObjectType::Circle)
		{
			return circleToRectangleCollision(otherObject, this);
		}

		return false;
	}
	static bool circleToRectangleCollision(GameObject* circle, GameObject* rectangle)
	{
		float testX = circle->screenPosition.x;
		float testY = circle->screenPosition.y;

		// Left edge
		if (circle->screenPosition.x < rectangle->screenPosition.x)
		{
			testX = rectangle->screenPosition.x;
		}
		// Right edge
		else if (circle->screenPosition.x > rectangle->screenPosition.x + rectangle->width)
		{
			testX = rectangle->screenPosition.x + rectangle->width;
		}

		// Top edge
		if (circle->screenPosition.y < rectangle->screenPosition.y)
		{
			testY = rectangle->screenPosition.y;
		}
		// Bottom edge
		else if (circle->screenPosition.y > rectangle->screenPosition.y + rectangle->height)
		{
			testY = rectangle->screenPosition.y + rectangle->height;
		}

		float distX = circle->screenPosition.x - testX;
		float distY = circle->screenPosition.y - testY;
		float distance = std::sqrt((distX * distX) + (distY * distY));
		if (distance <= circle->radius)
		{
			return true;
		}
		return false;
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

	float width;
	float height;
	float radius = 0.f;
};

