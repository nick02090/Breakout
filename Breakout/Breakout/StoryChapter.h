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
	StoryChapter(std::string path);
	/// <summary>
	/// Returns next line from the chapter.
	/// Returns PLAY when it's mid chapter and level should load.
	/// Returns END when chapter is done.
	/// </summary>
	/// <returns></returns>
	std::string getNextLine();
	/// <summary>
	/// Returns chapter's title
	/// </summary>
	/// <returns></returns>
	std::string getTitle();
	/// <summary>
	/// Returns chapter's level
	/// </summary>
	/// <returns></returns>
	std::string getPathToLevel();
private:
	int currentLineIndex = -1;
	std::string title;
	std::string pathToLevel;
	std::vector<std::string> lines;
};

