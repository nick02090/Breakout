#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
namespace util
{
	// Game constants
	const int HeadingFontSize = 40;
	const int ParagraphFontSize = 28;

	struct Position
	{
		float x;
		float y;
	};

	/// <summary>
	/// Determines whether the given position is within the screen range.
	/// </summary>
	/// <param name="position"></param>
	/// <param name="screenWidth"></param>
	/// <param name="screenHeight"></param>
	/// <returns></returns>
	static bool isValidPosition(Position position, int screenWidth, int screenHeight)
	{
		bool isValid = true;

		// It's not valid if it is below zero
		if (position.x < 0 || position.y < 0)
		{
			isValid = false;
		}
		// It's not valid if it is outside of the window screen size
		else if (position.x > screenWidth || position.y > screenHeight)
		{
			isValid = false;
		}

		return isValid;
	}

	/// <summary>
	/// Clamps the given value in a given range.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="n">Value to clamp</param>
	/// <param name="lower">Lower range value</param>
	/// <param name="upper">Upper range value</param>
	/// <returns></returns>
	template <typename T>
	T clamp(const T& n, const T& lower, const T& upper) {
		return std::max(lower, std::min(n, upper));
	}

	/// <summary>
	/// Loads and returns and optimized texture.
	/// </summary>
	/// <param name="renderer">Renderer that optimizes texture loading</param>
	/// <param name="path">Texture path location</param>
	/// <returns></returns>
	static SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string path)
	{
		// The final texture
		SDL_Texture* newTexture = NULL;

		// Load image at specified path
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		if (loadedSurface == NULL)
		{
			std::cout << "Unable to load image " << path.c_str() << "! SDL_Error: " << IMG_GetError() << std::endl;
		}
		else
		{
			// Create texture from surface pixels
			newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			if (newTexture == NULL)
			{
				std::cout << "Unable to create texture from " << path.c_str() << "! SDL_Error: " << SDL_GetError() << std::endl;
			}

			// Get rid of old loaded surface
			SDL_FreeSurface(loadedSurface);
		}

		return newTexture;
	}

	/// <summary>
	/// Draws a text on the screen.
	/// </summary>
	/// <param name="font">Text font</param>
	/// <param name="color">Color of the text</param>
	/// <param name="message">Message of the text</param>
	/// <param name="position">Text position on the screen</param>
	/// <param name="height">Height of the text</param>
	static void drawText(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, const char* message, Position position, int height)
	{
		// Create surface to put text on
		SDL_Surface* messageSurface = TTF_RenderText_Solid(font, message, color);

		// Convert the surface to a texture
		SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);

		// Create a rect to position the texture
		SDL_FRect messageRect;
		messageRect.x = position.x;
		messageRect.y = position.y;
		messageRect.w = static_cast<float>(std::strlen(message) * 25);
		messageRect.h = static_cast<float>(height);

		// Render the texture on the screen
		SDL_RenderCopyF(renderer, messageTexture, NULL, &messageRect);

		// Get rid of the surface and the texture
		SDL_FreeSurface(messageSurface);
		SDL_DestroyTexture(messageTexture);
	}

	/// <summary>
	/// Draws button on the screen.
	/// </summary>
	/// <param name="texture">Button texture</param>
	/// <param name="position">Button position on the screen</param>
	static void drawButton(SDL_Renderer* renderer, SDL_Texture* texture, Position position)
	{
		// Create a rect to position the texture
		SDL_FRect rect;
		rect.x = position.x;
		rect.y = position.y;
		rect.w = 270.f;
		rect.h = 70.f;

		// Render the texture on the screen
		SDL_RenderCopyF(renderer, texture, NULL, &rect);
	}
}