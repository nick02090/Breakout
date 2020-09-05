#pragma once
#include "GameScene.h"
#include "StoryChapter.h"
class StoryGameScene : public GameScene
{
public:

	enum class StoryState
	{
		NARRATION,
		PLAY,
		PAUSE
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

		// Initialize textures
		backgroundTransitionTexture = NULL;
		blackButtonTexture = NULL;
		whiteButtonTexture = NULL;

		// Initialize chapters
		firstChapter = new StoryChapter(FIRST_CHAPTER_PATH);
		secondChapter = new StoryChapter(SECOND_CHAPTER_PATH);
		thirdChapter = new StoryChapter(THIRD_CHAPTER_PATH);
		currentChapter = firstChapter;
		currentChapterLine = currentChapter->getNextLine();

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

		// Free loaded font
		TTF_CloseFont(font);
		font = NULL;
	}
	void update();
	void handleInput(SDL_Event* e);
	bool loadMedia();
private:
	void narrationHandleInput(SDL_Event* e);
	void playHandleInput(SDL_Event* e);
	void pauseHandleInput(SDL_Event* e);
	void narrationUpdate();
	void playUpdate();
	void pauseUpdate();

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

	StoryChapter* currentChapter;
	std::string currentChapterLine;

	TTF_Font* font;
};

