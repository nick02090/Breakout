#pragma once
#include <iostream>
#include <SDL_image.h>
namespace util
{
	/// <summary>
	/// Loads and returns and optimized texture.
	/// </summary>
	/// <param name="renderer">Renderer that optimizes texture loading</param>
	/// <param name="path">Texture path location</param>
	/// <returns></returns>
	SDL_Texture* loadTexture(SDL_Renderer* renderer, std::string path) 
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
}