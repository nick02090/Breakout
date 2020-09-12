#pragma once
#include "CircleGameObject.h"
class Ball : public CircleGameObject
{
public:

	enum class WallHit {
		Vertical,
		Horizontal,
		Default
	};

	Ball(SDL_Renderer* _renderer);
	/// <summary>
	/// Determines whether the ball has hit the screen bounds (wall).
	/// </summary>
	/// <returns></returns>
	bool hasHitWall();
	/// <summary>
	/// Returns previous wall that has been hit.
	/// </summary>
	/// <returns></returns>
	WallHit getPreviousWallHit();
	/// <summary>
	/// Determines whether the ball has went through the bottom screen bound (wall).
	/// </summary>
	/// <returns></returns>
	bool hasFellDown();
	/// <summary>
	/// Returns current ball velocity.
	/// </summary>
	/// <returns></returns>
	float getVelocity();
private:
	const std::string TexturePath = "GameObjects/Ball.png";
	const float Radius = 10.f;

	float velocity = 0.25f;
	WallHit previousWallHit;
};

