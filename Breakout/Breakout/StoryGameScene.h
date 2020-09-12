#pragma once
#include "GameScene.h"
#include "StoryChapter.h"
class StoryGameScene : public GameScene
{
public:

	enum class StoryState
	{
		Narration,
		Level
	};

	enum class StoryChapterState
	{
		FirstChapter,
		SecondChapter,
		ThirdChapter
	};

	StoryGameScene(SDL_Renderer* _renderer);
	~StoryGameScene();
	/// <summary>
	/// Updates the screen window.
	/// </summary>
	void update(float deltaTime);
	/// <summary>
	/// Handles input.
	/// </summary>
	void handleInput(SDL_Event* e);
	/// <summary>
	/// Loads required media.
	/// </summary>
	bool loadMedia();
private:
	/// <summary>
	/// Handles input when in narration state.
	/// </summary>
	void narrationHandleInput(SDL_Event* e);
	/// <summary>
	/// Handles input when in level state.
	/// </summary>
	void levelHandleInput(SDL_Event* e);
	/// <summary>
	/// Updates the screen window when in narration state.
	/// </summary>
	void narrationUpdate(float deltaTime);
	/// <summary>
	/// Updates the screen window when in level state.
	/// </summary>
	void levelUpdate(float deltaTime);
	/// <summary>
	/// Selected OK on the narration menu.
	/// </summary>
	void ok();

	const std::string FirstChapterPath = "Chapters/Chapter_I.xml";
	const std::string SecondChapterPath = "Chapters/Chapter_II.xml";
	const std::string ThirdChapterPath = "Chapters/Chapter_III.xml";

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

	Menu<StoryGameScene>* narrationMenu;
	Menu<StoryGameScene>::MenuRequest narrationMenuRequests[1] = { &StoryGameScene::ok };

	const util::Position OKButtonPosition = { 750.f, 700.f };
	const util::Position OKTextPosition = { 850.f, 720.f };
	std::vector<MenuButton> narrationMenuButtons{
		{ OKButtonPosition, OKTextPosition, "OK" }
	};

	TTF_Font* font;
};

