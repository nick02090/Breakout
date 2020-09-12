#pragma once
#include "GameObject.h"
class RectangleGameObject : public GameObject
{
public:
	RectangleGameObject(SDL_Renderer* _renderer);
	virtual ~RectangleGameObject();
	/// <summary>
	/// Renders rectangle object on the screen.
	/// </summary>
	/// <param name="widthFactor">Width factor that is applied to the width size of the rendered texture</param>
	/// <param name="heightFactor">Height factor that is applied to the height size of the rendered texture</param>
	void render(float _widthFactor = 1.0, float _heightFactor = 1.0);
	/// <summary>
	/// Returns width of the rectangle.
	/// </summary>
	/// <returns></returns>
	float getWidth();
	/// <summary>
	/// Returns height of the rectangle.
	/// </summary>
	/// <returns></returns>
	float getHeight();
protected:
	float width;
	float height;
};

