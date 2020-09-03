#pragma once
class Game
{
public:

	enum class GameState
	{
		PLAYING,
		PAUSE,
		MENU,
		WIN,
		LOSE
	};

	Game();
	void start();
	void update();
	void end();
private:
	GameState gameState;
};