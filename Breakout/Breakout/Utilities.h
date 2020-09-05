#pragma once
#include <iostream>
#include <SDL_image.h>
namespace util
{
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
}