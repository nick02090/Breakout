#include "Level.h"
#include "tinyxml2.h"
#include <sstream>
#include <string>

Level::Level(std::string path)
{
	// Initialize member variables via xmlDocument
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError eResult = doc.LoadFile(path.c_str());
	if (eResult == tinyxml2::XML_SUCCESS)
	{
		// Get Level node and it's attributes
		tinyxml2::XMLNode* levelNode = doc.FirstChild();
		tinyxml2::XMLElement* levelElement = levelNode->ToElement();
		rowCount = levelElement->FindAttribute("RowCount")->IntValue();
		columnCount = levelElement->FindAttribute("ColumnCount")->IntValue();
		rowSpacing = levelElement->FindAttribute("RowSpacing")->IntValue();
		columnSpacing = levelElement->FindAttribute("ColumnSpacing")->IntValue();
		backgroundTexturePath = levelElement->FindAttribute("BackgroundTexture")->Value();

		// Get BrickTypes node and it's attributes
		tinyxml2::XMLElement* brickTypesElement = levelElement->FirstChild()->ToElement();
		tinyxml2::XMLComment* nameComment = brickTypesElement->FirstChild()->ToComment();
		tinyxml2::XMLElement* brickElement = nameComment->NextSiblingElement();
		while (true)
		{
			// Create a new brick and add it to a list
			std::string name = nameComment->Value();
			name.erase(std::remove(name.begin(), name.end(), ' '), name.end());
			std::string id = brickElement->FindAttribute("Id")->Value();
			std::string texturePath = brickElement->FindAttribute("Texture")->Value();
			int hitPoints = brickElement->FindAttribute("HitPoints")->IntValue();
			std::string hitSoundPath = brickElement->FindAttribute("HitSound")->Value();
			std::string breakSoundPath = "";
			const char* breakSoundValue = brickElement->Attribute("BreakSound");
			if (breakSoundValue != NULL)
			{
				breakSoundPath = breakSoundValue;
			}
			int breakScore = 0;
			const char* breakScorevalue = brickElement->Attribute("BreakScore");
			if (breakScorevalue != NULL)
			{
				breakScore = std::stoi(breakScorevalue);
			}
			Brick* brick = new Brick(name, id, texturePath, hitPoints, hitSoundPath, breakSoundPath, breakScore);
			bricks.push_back(brick);
			// Get next brick if there is one
			tinyxml2::XMLNode* nextSibling = brickElement->NextSibling();
			if (nextSibling == NULL)
			{
				break;
			}
			nameComment = nextSibling->ToComment();
			brickElement = nameComment->NextSiblingElement();
		}

		// Get Bricks node and it'a attributes
		tinyxml2::XMLElement* bricksElement = brickTypesElement->NextSiblingElement();
		std::string text = bricksElement->GetText();
		std::istringstream iss(text);
		std::string line;
		while (std::getline(iss, line))
		{
			std::vector<std::string> lineResult;
			std::istringstream iss(line);
			for (std::string s; iss >> s; )
			{
				lineResult.push_back(s);
			}
			if (lineResult.size() > 0)
			{
				bricksLayout.push_back(lineResult);
			}
		}
	}
	else
	{
		std::cout << "Unable to load XML file " << path.c_str() << std::endl;
	}

}

void Level::load()
{
	// TODO: Needs to be implemented
}

void Level::play()
{
	// TODO: Needs to be implemented
}

void Level::pause()
{
	// TODO: Needs to be implemented
}