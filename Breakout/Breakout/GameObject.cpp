#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* _renderer) : renderer(_renderer)
{
	// Set default values for the member variables
	height = 0.f;
	width = 0.f;
	screenPosition = util::Position{ 0.f, 0.f };
	type = GameObjectType::Rectangle;
	verticalHitPosition = HitPosition::Default;
	horizontalHitPosition = HitPosition::Default;
}

bool GameObject::isInCollisionWith(GameObject* otherObject)
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

bool GameObject::circleToCircleCollision(GameObject* firstCircle, GameObject* secondCircle)
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
	float distance = std::sqrt((distX * distX) + (distY * distY));
	if (distance <= firstCircle->radius + secondCircle->radius)
	{
		return true;
	}
	return false;
}

bool GameObject::rectangleToRectangleCollision(GameObject* firstRectangle, GameObject* secondRectangle)
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

bool GameObject::circleToRectangleCollision(GameObject* circle, GameObject* rectangle)
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
		rectangle->verticalHitPosition = HitPosition::Top;
	}
	// Bottom edge
	else if (circleCenter.y > rectangle->screenPosition.y + rectangle->height)
	{
		testY = rectangle->screenPosition.y + rectangle->height;
		rectangle->verticalHitPosition = HitPosition::Bottom;
	}

	float distX = circleCenter.x - testX;
	float distY = circleCenter.y - testY;
	float distance = std::sqrt((distX * distX) + (distY * distY));
	if (distance <= circle->radius)
	{
		if (circleCenter.x <= rectangle->screenPosition.x + 15.f)
		{
			rectangle->horizontalHitPosition = HitPosition::LeftEdge;
		}
		else if (circleCenter.x >= rectangle->screenPosition.x + rectangle->width - 15.f)
		{
			rectangle->horizontalHitPosition = HitPosition::RightEdge;
		}
		return true;
	}
	rectangle->verticalHitPosition = HitPosition::Default;
	rectangle->horizontalHitPosition = HitPosition::Default;
	return false;
}

GameObject::HitPosition GameObject::getVerticalHitPosition()
{
	return verticalHitPosition;
}

GameObject::HitPosition GameObject::getHorizontalHitPosition()
{
	return horizontalHitPosition;
}