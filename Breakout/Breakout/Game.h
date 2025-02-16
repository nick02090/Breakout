#pragma once
struct SDL_Window;
struct SDL_Renderer;
class GameScene;
enum class GameState;
class Game
{
public:
	/// <summary>
	/// Initialize game and prepare everything for running.
	/// </summary>
	Game();
	/// <summary>
	/// Run game loop and display startup Main Menu.
	/// </summary>
	void start();
private:
	/// <summary>
	/// Initialize SDL and all of it's subsystems.
	/// </summary>
	/// <returns></returns>
	bool initSDL();
	/// <summary>
	/// Frees media and shuts down SDL.
	/// </summary>
	void end();
	/// <summary>
	/// Initializes a new scene based on a gameState and loads its media.
	/// </summary>
	void initScene();

	int screenWidth = 1024;
	int screenHeight = 768;
	SDL_Window* window;
	SDL_Renderer* renderer;
	GameState gameState;
	GameScene* gameScene;

	bool showFps = false;
	int fps = 0;
	int fpsPrint = 0;
	int previousTime = 0;
	int currentTime = 0;

	int last = 0;
	int now;
	float deltaTime = 0;
};