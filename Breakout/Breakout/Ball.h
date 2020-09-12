#pragma once
#include "GameObject.h"
class Ball : public GameObject
{
public:

	enum class WallHit {
		Vertical,
		Horizontal,
		Default
	};

	Ball(SDL_Renderer* _renderer);
	~Ball();
	/// <summary>
	/// Renders ball on the screen.
	/// </summary>
	/// <param name="_screenPosition">Screen position that the ball is rendered on</param>
	/// <param name="widthFactor">Width factor that is applied to the width size of the rendered ball texture</param>
	/// <param name="heightFactor">Height factor that is applied to the height size of the rendered ball texture</param>
	void render(util::Position _screenPosition, float widthFactor = 1.0, float heightFactor = 1.0);
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
	/// <summary>
	/// Path of the ball texture.
	/// </summary>
	const std::string TexturePath = "GameObjects/Ball.png";
	/// <summary>
	/// Width of the ball.
	/// </summary>
	const float Width = 20.f;
	/// <summary>
	/// Height of the ball.
	/// </summary>
	const float Height = 20.f;
	/// <summary>
	/// Radius of the ball.
	/// </summary>
	const float Radius = 10.f;

	float velocity = 0.25f;
	WallHit previousWallHit;
	SDL_Texture* texture;
};

