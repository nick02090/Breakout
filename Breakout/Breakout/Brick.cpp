#include "Brick.h"

Brick::Brick(SDL_Renderer* _renderer, std::string _name, std::string _id, std::string _texturePath, int _hitPoints,
	std::string _hitSoundPath, std::string _breakSoundPath, int _breakScore) : RectangleGameObject(_renderer), 
	name(_name), id(_id), texturePath(_texturePath), hitPoints(_hitPoints), hitSoundPath(_hitSoundPath), breakSoundPath(_breakSoundPath), breakScore(_breakScore)
{
	// Initialize member variables
	timesHit = 0;
	width = Width;
	height = Height;
	// Load the bricks texture
	texture = util::loadTexture(renderer, texturePath);
	// Load the bricks sounds
	breakSound = Mix_LoadWAV(breakSoundPath.c_str());
	hitSound = Mix_LoadWAV(hitSoundPath.c_str());
}

Brick::Brick(Brick* _brick) : Brick(_brick->renderer, _brick->name, _brick->id, _brick->texturePath, _brick->hitPoints, _brick->hitSoundPath, _brick->breakSoundPath, _brick->breakScore)
{
	isEmpty = _brick->isEmpty;
}

Brick::Brick(SDL_Renderer* _renderer, std::string _name, std::string _id) : RectangleGameObject(_renderer), name(_name), id(_id)
{
	// Initialize member variables
	timesHit = 0;
	breakScore = 0;
	hitPoints = 0;
	isEmpty = true;
	breakSound = NULL;
	hitSound = NULL;
}

Brick::~Brick()
{
	// Free the sound effects
	Mix_FreeChunk(breakSound);
	Mix_FreeChunk(hitSound);
	breakSound = NULL;
	hitSound = NULL;
}

void Brick::hit()
{
	timesHit += 1;
	if (timesHit == hitPoints)
	{
		isCrushed = true;
		Mix_PlayChannel(-1, breakSound, 0);
	}
	else
	{
		Mix_PlayChannel(-1, hitSound, 0);
	}
}

bool Brick::getIsCrushed()
{
	return isCrushed;
}

bool Brick::getIsEmpty()
{
	return isEmpty;
}

int Brick::getBreakScore()
{
	return breakScore;
}

std::string Brick::getId()
{
	return id;
}

bool Brick::isBreakable()
{
	return hitPoints > 0;
}

void Brick::reset()
{
	timesHit = 0;
	isCrushed = false;
}