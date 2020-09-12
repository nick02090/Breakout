#include "Brick.h"

Brick::Brick(SDL_Renderer* _renderer, std::string _name, std::string _id, std::string _texturePath, int _hitPoints,
	std::string _hitSoundPath, std::string _breakSoundPath, int _breakScore) : GameObject(_renderer, GameObjectType::Rectangle), 
	name(_name), id(_id), texturePath(_texturePath), hitPoints(_hitPoints), hitSoundPath(_hitSoundPath), breakSoundPath(_breakSoundPath), breakScore(_breakScore)
{
	// Initialize member variables
	timesHit = 0;
	// Load all necessary assets
	texture = util::loadTexture(renderer, texturePath);
	// Set brick size
	width = Width;
	height = Height;
	// Set brick size factors
	widthFactor = 1.f;
	heightFactor = 1.f;
}

Brick::Brick(Brick* _brick) : Brick(_brick->renderer, _brick->name, _brick->id, _brick->texturePath, _brick->hitPoints, _brick->hitSoundPath, _brick->breakSoundPath, _brick->breakScore)
{
	isEmpty = _brick->isEmpty;
}

Brick::Brick(SDL_Renderer* _renderer, std::string _name, std::string _id) : GameObject(_renderer, GameObjectType::Rectangle), name(_name), id(_id)
{
	type = GameObjectType::Rectangle;
	timesHit = 0;
	texture = NULL;
	breakScore = 0;
	hitPoints = 0;
	isEmpty = true;
}

Brick::~Brick()
{
	// Free loaded images
	SDL_DestroyTexture(texture);
	texture = NULL;
}

void Brick::render(util::Position _screenPosition, float _widthFactor, float _heightFactor)
{
	// Update scale factors
	widthFactor = _widthFactor;
	heightFactor = _heightFactor;

	// Update position on the screen
	screenPosition = _screenPosition;

	// Create a rect to position the texture
	SDL_FRect rect;
	rect.x = screenPosition.x;
	rect.y = screenPosition.y;
	rect.w = width / widthFactor;
	rect.h = height / heightFactor;

	// Render the texture on the screen
	SDL_RenderCopyF(renderer, texture, NULL, &rect);
}

void Brick::hit()
{
	timesHit += 1;
	if (timesHit == hitPoints)
	{
		isCrushed = true;
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