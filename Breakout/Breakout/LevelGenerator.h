#pragma once
#include "Level.h"
class LevelGenerator
{
public:
	LevelGenerator(SDL_Renderer* _renderer);
	~LevelGenerator();
	/// <summary>
	/// Returns new randomly generated level.
	/// </summary>
	/// <returns></returns>
	Level* generate(Player* player);
private:
	const std::string LevelNames[6] = {
		"Bricks",
		"Prison",
		"Stars",
		"Meadow",
		"Room",
		"Golden"
	};
	const std::string BackgroundTexturesPath[6] = {
		"Textures/Randoms/Bricks.png",
		"Textures/Randoms/Prison.png",
		"Textures/Randoms/Stars.png",
		"Textures/Randoms/Meadow.png",
		"Textures/Randoms/Room.png",
		"Textures/Randoms/Golden.png"
	};
	const std::string BackgroundMusicPath[8] = {
		"Audio/Soundtracks/bensound-allthat.mp3",
		"Audio/Soundtracks/bensound-badass.mp3",
		"Audio/Soundtracks/bensound-downtown.mp3",
		"Audio/Soundtracks/bensound-funkysuspense.mp3",
		"Audio/Soundtracks/bensound-groovyhiphop.mp3",
		"Audio/Soundtracks/bensound-hipjazz.mp3",
		"Audio/Soundtracks/bensound-retrosoul.mp3",
		"Audio/Soundtracks/bensound-sexy.mp3"
	};
	const int MinRowCount = 20;
	const int MaxRowCount = 40;
	const int MinColumnCount = 15;
	const int MaxColumnCount = 25;
	const int MinSpacing = 2;
	const int MaxSpacing = 6;
	const int MaxRows = 10;
	const int MinRows = 3;
	/// <summary>
	/// Maximum width of the screen that can be used for rendering bricks layout.
	/// </summary>
	const float MaxBricksWidth = 1004.f;
	/// <summary>
	/// Maximum height of the screen that can be used for rendering bricks layout.
	/// </summary>
	const float MaxBricksHeight = 600.f;
	/// <summary>
	/// Height of a one unscaled brick.
	/// </summary>
	const float BrickHeight = 20.f;
	/// <summary>
	/// Widht of a one unscaled brick.
	/// </summary>
	const float BrickWidth = 50.f;

	std::vector<Brick*> bricks;
	SDL_Renderer* renderer;
};

