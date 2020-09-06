#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include "tinyxml2.h"
class StoryChapter
{
public:
	StoryChapter(std::string path) 
	{
		// Parse the file chapter via tinyxml
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLError eResult = doc.LoadFile(path.c_str());
		if (eResult == tinyxml2::XML_SUCCESS)
		{
			// Get Chapter node and it's attributes
			tinyxml2::XMLNode* chapterNode = doc.FirstChild();
			tinyxml2::XMLElement* chapterElement = chapterNode->ToElement();
			title = chapterElement->FindAttribute("Title")->Value();
			pathToLevel = chapterElement->FindAttribute("Level")->Value();

			// Get Lines node and it's attributes
			tinyxml2::XMLNode* linesNode = chapterElement->FirstChild();
			tinyxml2::XMLElement* linesElement = linesNode->ToElement();
			std::string text = linesElement->GetText();

			// Add lines to a list
			std::istringstream iss(text);
			std::string line;
			while (std::getline(iss, line))
			{
				// Remove all tabs from the line
				line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
				if (!line.empty())
				{
					lines.push_back(line);
				}
			}
		}
		else
		{
			std::cout << "Unable to load XML file " << path.c_str() << std::endl;
		}
	}
	/// <summary>
	/// Returns next line from the chapter.
	/// Returns PLAY when it's mid chapter and level should load.
	/// Returns END when chapter is done.
	/// </summary>
	/// <returns></returns>
	std::string getNextLine()
	{
		// Increase line counter
		currentLineIndex += 1;
		// Check if there is more lines in the chapter
		if (currentLineIndex < static_cast<int>(lines.size()))
		{
			return lines.at(currentLineIndex);
		}
		else
		{
			return "END";
		}
	}
	/// <summary>
	/// Returns chapter's title
	/// </summary>
	/// <returns></returns>
	inline std::string getTitle()
	{
		return title;
	}
	/// <summary>
	/// Returns chapter's level
	/// </summary>
	/// <returns></returns>
	inline std::string getPathToLevel()
	{
		return pathToLevel;
	}
private:
	int currentLineIndex = -1;
	std::string title;
	std::string pathToLevel;
	std::vector<std::string> lines;
};

