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
			return rectangleToRectangleCollision(this, otherObject);
		}
		// Circle - Circle collision check
		else if (type == GameObjectType::Circle && otherObject->type == GameObjectType::Circle)
		{
			return circleToCircleCollision(this, otherObject);
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
	static bool circleToCircleCollision(GameObject* firstCircle, GameObject* secondCircle)
	{
		util::Position firstCircleCenter = {
			firstCircle->screenPosition.x + firstCircle->radius,
			firstCircle->screenPosition.y + firstCircle->radius
		};

		util::Position secondCircleCenter = {
			secondCircle->screenPosition.x + secondCircle->radius,
			secondCircle->screenPosition.y + secondCircle->radius
		};

		float distX = firstCircleCenter.x - secondCircleCenter.x;
		float distY = firstCircleCenter.y - secondCircleCenter.y;
		float distance = std::sqrt((distX*distX) + (distY*distY));
		if (distance <= firstCircle->radius + secondCircle->radius)
		{
			return true;
		}
		return false;
	}
	static bool rectangleToRectangleCollision(GameObject* firstRectangle, GameObject* secondRectangle)
	{
		if (firstRectangle->screenPosition.x + firstRectangle->width >= secondRectangle->screenPosition.x
			&& firstRectangle->screenPosition.x <= secondRectangle->screenPosition.x + secondRectangle->width
			&& firstRectangle->screenPosition.y + firstRectangle->height >= secondRectangle->screenPosition.y
			&& firstRectangle->screenPosition.y <= secondRectangle->screenPosition.y + secondRectangle->height)
		{
			return true;
		}
		return false;
	}
	static bool circleToRectangleCollision(GameObject* circle, GameObject* rectangle)
	{
		util::Position circleCenter = { 
			circle->screenPosition.x + circle->radius, 
			circle->screenPosition.y + circle->radius 
		};

		float testX = circleCenter.x;
		float testY = circleCenter.y;

		// Left edge
		if (circleCenter.x < rectangle->screenPosition.x)
		{
			testX = rectangle->screenPosition.x;
		}
		// Right edge
		else if (circleCenter.x > rectangle->screenPosition.x + rectangle->width)
		{
			testX = rectangle->screenPosition.x + rectangle->width;
		}

		// Top edge
		if (circleCenter.y < rectangle->screenPosition.y)
		{
			testY = rectangle->screenPosition.y;
			rectangle->isHitFromTop = true;
		}
		// Bottom edge
		else if (circleCenter.y > rectangle->screenPosition.y + rectangle->height)
		{
			testY = rectangle->screenPosition.y + rectangle->height;
			rectangle->isHitFromBottom = true;
		}

		float distX = circleCenter.x - testX;
		float distY = circleCenter.y - testY;
		float distance = std::sqrt((distX * distX) + (distY * distY));
		if (distance <= circle->radius)
		{
			if (circleCenter.x <= rectangle->screenPosition.x + 15.f) 
			{
				rectangle->isHitFromLeftEdge = true;
			}
			else if (circleCenter.x >= rectangle->screenPosition.x + rectangle->width - 15.f)
			{
				rectangle->isHitFromRightEdge = true;
			}
			return true;
		}
		rectangle->isHitFromLeftEdge = false;
		rectangle->isHitFromRightEdge = false;
		rectangle->isHitFromTop = false;
		rectangle->isHitFromBottom = false;
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

	bool isHitFromLeftEdge = false;
	bool isHitFromRightEdge = false;
	bool isHitFromTop = false;
	bool isHitFromBottom = false;
	float width;
	float height;
	float radius = 0.f;
};

