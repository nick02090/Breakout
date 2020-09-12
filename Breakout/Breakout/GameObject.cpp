#include "GameObject.h"
#include "CircleGameObject.h"
#include "RectangleGameObject.h"

GameObject::GameObject(SDL_Renderer* _renderer, GameObjectType _type) : renderer(_renderer), type(_type)
{
	// Set default values for the member variables
	heightFactor = 1.f;
	widthFactor = 1.f;
	screenPosition = util::Position{ 0.f, 0.f };
	verticalHitPosition = HitPosition::Default;
	horizontalHitPosition = HitPosition::Default;
	texture = NULL;
}

GameObject::~GameObject()
{
	// Free loaded images
	SDL_DestroyTexture(texture);
	texture = NULL;
}

bool GameObject::isInCollisionWith(GameObject* otherObject)
{
	// Rectangle - Rectangle collision check
	if (type == GameObjectType::Rectangle && otherObject->type == GameObjectType::Rectangle)
	{
		return rectangleToRectangleCollision(static_cast<RectangleGameObject*>(this), static_cast<RectangleGameObject*>(otherObject));
	}
	// Circle - Circle collision check
	else if (type == GameObjectType::Circle && otherObject->type == GameObjectType::Circle)
	{
		return circleToCircleCollision(static_cast<CircleGameObject*>(this), static_cast<CircleGameObject*>(otherObject));
	}
	// Circle - Rectangle collision check
	else if (type == GameObjectType::Circle && otherObject->type == GameObjectType::Rectangle)
	{
		return circleToRectangleCollision(static_cast<CircleGameObject*>(this), static_cast<RectangleGameObject*>(otherObject));
	}
	// Rectangle - Circle check
	else if (type == GameObjectType::Rectangle && otherObject->type == GameObjectType::Circle)
	{
		return circleToRectangleCollision(static_cast<CircleGameObject*>(otherObject), static_cast<RectangleGameObject*>(this));
	}

	return false;
}

bool GameObject::circleToCircleCollision(CircleGameObject* firstCircle, CircleGameObject* secondCircle)
{
	util::Position firstCircleCenter = {
		firstCircle->screenPosition.x + firstCircle->getRadius(),
		firstCircle->screenPosition.y + firstCircle->getRadius()
	};

	util::Position secondCircleCenter = {
		secondCircle->screenPosition.x + secondCircle->getRadius(),
		secondCircle->screenPosition.y + secondCircle->getRadius()
	};

	float distX = firstCircleCenter.x - secondCircleCenter.x;
	float distY = firstCircleCenter.y - secondCircleCenter.y;
	float distance = std::sqrt((distX * distX) + (distY * distY));
	if (distance <= firstCircle->getRadius() + secondCircle->getRadius())
	{
		return true;
	}
	return false;
}

bool GameObject::rectangleToRectangleCollision(RectangleGameObject* firstRectangle, RectangleGameObject* secondRectangle)
{
	if (firstRectangle->screenPosition.x + firstRectangle->getWidth() / firstRectangle->widthFactor >= secondRectangle->screenPosition.x
		&& firstRectangle->screenPosition.x <= secondRectangle->screenPosition.x + secondRectangle->getWidth() / secondRectangle->widthFactor
		&& firstRectangle->screenPosition.y + firstRectangle->getHeight() / firstRectangle->heightFactor >= secondRectangle->screenPosition.y
		&& firstRectangle->screenPosition.y <= secondRectangle->screenPosition.y + secondRectangle->getHeight() / secondRectangle->heightFactor)
	{
		return true;
	}
	return false;
}

bool GameObject::circleToRectangleCollision(CircleGameObject* circle, RectangleGameObject* rectangle)
{
	util::Position circleCenter = {
		circle->screenPosition.x + circle->getRadius(),
		circle->screenPosition.y + circle->getRadius()
	};

	float testX = circleCenter.x;
	float testY = circleCenter.y;

	// Left edge
	if (circleCenter.x < rectangle->screenPosition.x)
	{
		testX = rectangle->screenPosition.x;
	}
	// Right edge
	else if (circleCenter.x > rectangle->screenPosition.x + rectangle->getWidth() / rectangle->widthFactor)
	{
		testX = rectangle->screenPosition.x + rectangle->getWidth() / rectangle->widthFactor;
	}

	// Top edge
	if (circleCenter.y < rectangle->screenPosition.y)
	{
		testY = rectangle->screenPosition.y;
		rectangle->verticalHitPosition = HitPosition::Top;
	}
	// Bottom edge
	else if (circleCenter.y > rectangle->screenPosition.y + rectangle->getHeight() / rectangle->heightFactor)
	{
		testY = rectangle->screenPosition.y + rectangle->getHeight() / rectangle->heightFactor;
		rectangle->verticalHitPosition = HitPosition::Bottom;
	}

	float distX = circleCenter.x - testX;
	float distY = circleCenter.y - testY;
	float distance = std::sqrt((distX * distX) + (distY * distY));
	if (distance <= circle->getRadius())
	{
		if (circleCenter.x <= rectangle->screenPosition.x + 15.f)
		{
			rectangle->horizontalHitPosition = HitPosition::LeftEdge;
		}
		else if (circleCenter.x >= rectangle->screenPosition.x + rectangle->getWidth() - 15.f)
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