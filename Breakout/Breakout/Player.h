#pragma once
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player(SDL_Renderer* _renderer);
	~Player();
	/// <summary>
	/// Renders the player on the screen.
	/// </summary>
	/// <param name="_screenPosition">Screen position that the player is rendered on</param>
	/// <param name="widthFactor">Width factor that is applied to the width size of the rendered player texture</param>
	/// <param name="heightFactor">Height factor that is applied to the height size of the rendered player texture</param>
	void render(util::Position _screenPosition, float widthFactor = 1.0, float heightFactor = 1.0);
	/// <summary>
	/// Add points to the player score.
	/// </summary>
	/// <param name="value">Value which is added to the score</param>
	void addToScore(int value);
	/// <summary>
	/// Returns current score collected by the player.
	/// </summary>
	/// <returns></returns>
	int getCurrentScore();
	/// <summary>
	/// Returns current reamaining lives of the player.
	/// </summary>
	/// <returns></returns>
	int getCurrentLives();
	/// <summary>
	/// Reduces current reamaining lives by one.
	/// </summary>
	void reduceLives();
	/// <summary>
	/// Determines whether the player is dead or not.
	/// </summary>
	/// <returns></returns>
	bool isDead();
	/// <summary>
	/// Resets players' parameters to initial values.
	/// </summary>
	void reset();
	/// <summary>
	/// Sets the player acceleration to zero (0).
	/// </summary>
	void turnOffAcceleration();
	/// <summary>
	/// Increases the acceleration of the player in desired axis.
	/// </summary>
	/// <param name="isNegativeXAxis">True for left, false for right side</param>
	void increaseAcceleration(bool isNegativeXAxis);
	/// <summary>
	/// Returns current velocity of the player.
	/// </summary>
	/// <returns></returns>
	float getVelocity();
private:
	const std::string TexturePath = "GameObjects/Player.png";
	const int MaxLives = 5;

	const float Width = 100.f;
	const float Height = 20.f;

	SDL_Texture* texture;

	int currentLives;
	int currentScore;

	const float MinVelocity = 10.f;
	const float MaxVelocity = 50.f;
	float acceleration = 0.f;
	float velocity = MinVelocity;
	float velocityMultiplier = -1.f;
};

