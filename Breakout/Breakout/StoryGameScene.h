#pragma once
#include "GameScene.h"
#include "StoryChapter.h"
class StoryGameScene : public GameScene
{
public:

	enum class StoryState
	{
		NARRATION,
		LEVEL
	};

	enum class StoryChapterState
	{
		FIRST_CHAPTER,
		SECOND_CHAPTER,
		THIRD_CHAPTER
	};

	StoryGameScene(SDL_Renderer* _renderer) : GameScene(_renderer)
	{
		// Initialize member variables
		storyState = StoryState::NARRATION;

		// Initialize the player
		player = new Player(_renderer);

		// Initialize textures
		backgroundTransitionTexture = NULL;
		blackButtonTexture = NULL;
		whiteButtonTexture = NULL;

		// Initialize chapters
		firstChapter = new StoryChapter(FIRST_CHAPTER_PATH);
		secondChapter = new StoryChapter(SECOND_CHAPTER_PATH);
		thirdChapter = new StoryChapter(THIRD_CHAPTER_PATH);
		chapters[0] = firstChapter;
		chapters[1] = secondChapter;
		chapters[2] = thirdChapter;
		StoryChapter* currentChapter = chapters[currentChapterIndex];
		currentChapterLine = currentChapter->getNextLine();
		currentLevel = NULL;

		// Initialize font
		font = NULL;
	}
	~StoryGameScene()
	{
		// Free loaded images
		SDL_DestroyTexture(backgroundTransitionTexture);
		backgroundTransitionTexture = NULL;
		SDL_DestroyTexture(blackButtonTexture);
		blackButtonTexture = NULL;
		SDL_DestroyTexture(whiteButtonTexture);
		whiteButtonTexture = NULL;

		// Delete the player
		delete player;

		// Free loaded font
		TTF_CloseFont(font);
		font = NULL;
	}
	void update();
	void handleInput(SDL_Event* e);
	bool loadMedia();
private:
	void narrationHandleInput(SDL_Event* e);
	void levelHandleInput(SDL_Event* e);
	void narrationUpdate();
	void levelUpdate();

	const std::string FIRST_CHAPTER_PATH = "Chapters/Chapter_I.xml";
	const std::string SECOND_CHAPTER_PATH = "Chapters/Chapter_II.xml";
	const std::string THIRD_CHAPTER_PATH = "Chapters/Chapter_III.xml";

	StoryState storyState;

	SDL_Texture* backgroundTransitionTexture;
	SDL_Texture* blackButtonTexture;
	SDL_Texture* whiteButtonTexture;

	StoryChapter* firstChapter;
	StoryChapter* secondChapter;
	StoryChapter* thirdChapter;
	StoryChapter* chapters[3];

	int currentChapterIndex = 0;
	std::string currentChapterLine;

	Level* currentLevel;
	Player* player;

	TTF_Font* font;
};

