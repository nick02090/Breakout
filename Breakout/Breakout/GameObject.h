#pragma once
#include "Utilities.h"
class CircleGameObject;
class RectangleGameObject;
class GameObject
{
public:

	enum class GameObjectType
	{
		Rectangle,
		Circle
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
	virtual ~GameObject();
	/// <summary>
	/// Renders an object on the screen by creating a copy of the object.
	/// </summary>
	/// <param name="widthFactor">Width scaling factor that scales down objects width</param>
	/// <param name="heightFactor">Height scaling factor that scales down objects height</param>
	virtual void render(float widthFactor = 1.0, float heightFactor = 1.0) = 0;
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
	static bool circleToCircleCollision(CircleGameObject* firstCircle, CircleGameObject* secondCircle);
	/// <summary>
	/// Determines whether the two objects are colliding, considering that they're both rectangles.
	/// </summary>
	/// <param name="firstRectangle">First rectangle object</param>
	/// <param name="secondRectangle">Second rectangle object</param>
	/// <returns></returns>
	static bool rectangleToRectangleCollision(RectangleGameObject* firstRectangle, RectangleGameObject* secondRectangle);
	/// <summary>
	/// Determines whether the two objects are colliding, considering that one is a circle and the other one is a rectangle.
	/// </summary>
	/// <param name="circle">Circle object</param>
	/// <param name="rectangle">Rectangle object</param>
	/// <returns></returns>
	static bool circleToRectangleCollision(CircleGameObject* circle, RectangleGameObject* rectangle);
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

	util::Position screenPosition;
protected:
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	GameObjectType type;

	HitPosition verticalHitPosition;
	HitPosition horizontalHitPosition;

	float widthFactor;
	float heightFactor;
};

