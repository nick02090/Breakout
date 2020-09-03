#pragma once
namespace tinyxml2 
{
	class XMLDocument;
}
class SDL_Texture;
namespace util
{
	class Array2D;
}

class Level
{
public:
	Level(tinyxml2::XMLDocument xmlDocument);
	void load();
	void play();
	void pause();
private:
	int rowCount;
	int columnCount;
	int rowSpacing;
	int columnSpacing;
	SDL_Texture* backgroundTexture;
	util::Array2D* bricksLayout;
};

