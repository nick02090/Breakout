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

	enum class HitPosition 
	{
		LeftEdge,
		RightEdge,
		Top,
		Bottom,
		Default
	};

	GameObject(SDL_Renderer* _renderer, GameObjectType _type);
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
	bool isInCollisionWith(GameObject* otherObject);
	/// <summary>
	/// Determines whether the two objects are colliding, considering that they're both circles.
	/// </summary>
	/// <param name="firstCircle">First circle object</param>
	/// <param name="secondCircle">Second circle object</param>
	/// <returns></returns>
	static bool circleToCircleCollision(GameObject* firstCircle, GameObject* secondCircle);
	/// <summary>
	/// Determines whether the two objects are colliding, considering that they're both rectangles.
	/// </summary>
	/// <param name="firstRectangle">First rectangle object</param>
	/// <param name="secondRectangle">Second rectangle object</param>
	/// <returns></returns>
	static bool rectangleToRectangleCollision(GameObject* firstRectangle, GameObject* secondRectangle);
	/// <summary>
	/// Determines whether the two objects are colliding, considering that one is a circle and the other one is a rectangle.
	/// </summary>
	/// <param name="circle">Circle object</param>
	/// <param name="rectangle">Rectangle object</param>
	/// <returns></returns>
	static bool circleToRectangleCollision(GameObject* circle, GameObject* rectangle);
	/// <summary>
	/// Determines from which vertical side/position has an object been hit.
	/// </summary>
	/// <returns></returns>
	HitPosition getVerticalHitPosition();
	/// <summary>
	/// Determines from which horizontal side/position has an object been hit.
	/// </summary>
	/// <returns></returns>
	HitPosition getHorizontalHitPosition();
protected:
	GameObjectType type;
	util::Position screenPosition;
	SDL_Renderer* renderer;

	HitPosition verticalHitPosition;
	HitPosition horizontalHitPosition;
	float width;
	float height;
	float radius;
};

