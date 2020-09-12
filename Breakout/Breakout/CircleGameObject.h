#pragma once
#include "GameObject.h"
class CircleGameObject : public GameObject
{
public:
	CircleGameObject(SDL_Renderer* _renderer);
	/// <summary>
	/// Renders circle object on the screen.
	/// </summary>
	/// <param name="_screenPosition">Screen position that the circle is rendered on</param>
	/// <param name="widthFactor">Width factor that is applied to the width size of the rendered texture</param>
	/// <param name="heightFactor">Height factor that is applied to the height size of the rendered texture</param>
	void render(float _widthFactor = 1.0, float _heightFactor = 1.0);
	/// <summary>
	/// Returns radius of the circle.
	/// </summary>
	/// <returns></returns>
	float getRadius();
protected:
	float radius;
};

