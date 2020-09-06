#pragma once
#include <iostream>
#include <vector>
#include "Brick.h"
namespace util
{
	class Array2D;
}

class Level
{
public:
	Level(std::string path);
	void load();
	void play();
	void pause();
private:
	int rowCount;
	int columnCount;
	int rowSpacing;
	int columnSpacing;
	std::string backgroundTexturePath;
	std::vector<std::vector<std::string>> bricksLayout;

	std::vector<Brick*> bricks;
};

