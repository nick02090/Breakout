#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Utilities.h"

enum class GameState
{
	MAIN_MENU,
	STORY,
	ARCADE,
	COOP,
	DEFAULT
};


class GameScene
{
public:
	GameScene(SDL_Renderer* _renderer) : renderer(_renderer) 
	{
		// Initialize screenWidth and screenHeight
		SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);

		// Initialize nextGameState
		nextGameState = GameState::DEFAULT;
	}
	virtual ~GameScene() {}
	/// <summary>
	/// Updates the screen window.
	/// </summary>
	virtual void update() = 0;
	/// <summary>
	/// Handles input.
	/// </summary>
	virtual void handleInput(SDL_Event* e) = 0;
	/// <summary>
	/// Loads required media.
	/// </summary>
	virtual bool loadMedia() = 0;
	/// <summary>
	/// Returns current should quit state.
	/// </summary>
	/// <returns></returns>
	bool hasRequestedToQuit()
	{
		return shouldQuit;
	}
	/// <summary>
	/// Returns true if the scene has request to change to another one.
	/// </summary>
	/// <returns></returns>
	bool hasRequestNextGameState()
	{
		// If nextGameState has been set then the scene requested a change
		if (nextGameState != GameState::DEFAULT)
		{
			return true;
		}
		else 
		{
			return false;
		}
	}
	/// <summary>
	/// Returns next game state.
	/// </summary>
	/// <returns></returns>
	GameState getNextGameState()
	{
		return nextGameState;
	}
protected:

	struct Position
	{
		int x;
		int y;
	};

	/// <summary>
	/// Determines whether the given position is within the screen range.
	/// </summary>
	/// <param name="position"></param>
	/// <returns></returns>
	bool isValidPosition(Position position)
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
	/// Loads and returns and optimized texture.
	/// </summary>
	/// <param name="renderer">Renderer that optimizes texture loading</param>
	/// <param name="path">Texture path location</param>
	/// <returns></returns>
	SDL_Texture* loadTexture(std::string path)
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
	void drawText(TTF_Font* font, SDL_Color color, const char* message, Position position, int height)
	{
		// Create surface to put text on
		SDL_Surface* messageSurface = TTF_RenderText_Solid(font, message, color);

		// Convert the surface to a texture
		SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);

		// Create a rect to position the texture
		SDL_Rect messageRect;
		messageRect.x = position.x;
		messageRect.y = position.y;
		messageRect.w = std::strlen(message) * 25;
		messageRect.h = height;

		// Render the texture on the screen
		SDL_RenderCopy(renderer, messageTexture, NULL, &messageRect);

		// Get rid of the surface and the texture
		SDL_FreeSurface(messageSurface);
		SDL_DestroyTexture(messageTexture);
	}
	/// <summary>
	/// Draws button on the screen.
	/// </summary>
	/// <param name="texture">Button texture</param>
	/// <param name="position">Button position on the screen</param>
	void drawButton(SDL_Texture* texture, Position position)
	{
		// Create a rect to position the texture
		SDL_Rect rect;
		rect.x = position.x;
		rect.y = position.y;
		rect.w = 270;
		rect.h = 70;

		// Render the texture on the screen
		SDL_RenderCopy(renderer, texture, NULL, &rect);
	}

	const int HEADING_FONT_SIZE = 40;
	const int PARAGRAPH_FONT_SIZE = 28;

	SDL_Renderer* renderer;
	int screenWidth, screenHeight;
	bool shouldQuit = false;
	GameState nextGameState;
};

