#include "Level.h"

Level::Level(std::string path, SDL_Renderer* _renderer, Player* _player, std::string _name, bool _isRetryable) : 
	renderer(_renderer), player(_player), name(_name), isRetryable(_isRetryable)
{
	// Initialize ball for the level
	ball = new Ball(renderer);

	// Initialize all of the menus
	if (isRetryable)
	{
		// Initialize pause menu
		pauseMenu = new Menu<Level>(retryablePauseMenuButtons, renderer, retryablePauseMenuRequests, this);
		// Initialize lose end level menu
		loseEndLevelMenu = new Menu<Level>(retryableLoseEndLevelMenuButtons, renderer, retryableLoseEndLevelMenuRequests, this);
	} 
	else
	{
		// Initialize pause menu
		pauseMenu = new Menu<Level>(nonRetryablePauseMenuButtons, renderer, nonRetryablePauseMenuRequests, this);
		// Initialize lose end level menu
		loseEndLevelMenu = new Menu<Level>(nonRetryableLoseEndLevelMenuButtons, renderer, nonRetryableLoseEndLevelMenuRequests, this);
	}
	// Initialize win end level menu
	winEndLevelMenu = new Menu<Level>(winEndLevelMenuButtons, renderer, winEndLevelMenuRequests, this);

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
		backgroundMusicPath = levelElement->FindAttribute("Soundtrack")->Value();

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
			Brick* brick = new Brick(_renderer, name, id, texturePath, hitPoints, hitSoundPath, breakSoundPath, breakScore);
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
		Brick* emptyBrick = new Brick(_renderer, "EmptyBrick", "_");
		bricks.push_back(emptyBrick);

		// Calculate bricks screen factors
		float neededBrickWidth = columnCount * BrickWidth + (columnCount - 1) * rowSpacing;
		float neededBrickHeight = rowCount * BrickHeight + (rowCount - 1) * columnSpacing;
		bricksWidthFactor = neededBrickWidth / MaxBricksWidth;
		bricksHeightFactor = neededBrickHeight / MaxBricksHeight;

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
				int row = static_cast<int>(bricksLayout.size());
				std::vector<Brick*> bricksRow;
				std::vector<util::Position> bricksRowPositions;
				for (std::string id : lineResult)
				{
					for (Brick* brick : bricks)
					{
						if (brick->getId()._Equal(id))
						{
							int col = static_cast<int>(bricksRow.size());
							float x = firstBrickPosition.x + col * (BrickWidth + columnSpacing) / bricksWidthFactor;
							float y = firstBrickPosition.y + row * (BrickHeight + rowSpacing) / bricksHeightFactor;
							if (brick->getIsEmpty())
							{
								bricksRow.push_back(new Brick(_renderer, "EmptyBrick", "_"));
							}
							else 
							{
								bricksRow.push_back(new Brick(brick));
							}
							bricksRowPositions.push_back({x, y});
							break;
						}
					}
				}
				bricksPositions.push_back(bricksRowPositions);
				bricksLayout.push_back(bricksRow);
			}
		}
	}
	else
	{
		std::cout << "Unable to load XML file " << path.c_str() << std::endl;
	}
}

Level::~Level()
{
	// Delete the bricks
	for (auto brick : bricks)
	{
		delete brick;
	}
	bricks.clear();
	// Delete the bricks layout
	for (auto brickRow : bricksLayout)
	{
		for (auto brick : brickRow)
		{
			delete brick;
		}
		brickRow.clear();
	}
	bricksLayout.clear();
	// Delete menus
	delete pauseMenu;
	pauseMenu = NULL;
	delete loseEndLevelMenu;
	loseEndLevelMenu = NULL;
	delete winEndLevelMenu;
	winEndLevelMenu = NULL;
	// Delete menu buttons
	retryablePauseMenuButtons.clear();
	nonRetryablePauseMenuButtons.clear();
	retryableLoseEndLevelMenuButtons.clear();
	nonRetryableLoseEndLevelMenuButtons.clear();
	winEndLevelMenuButtons.clear();

	// Free loaded images
	SDL_DestroyTexture(backgroundTexture);
	backgroundTexture = NULL;
	SDL_DestroyTexture(HUDTexture);
	HUDTexture = NULL;

	// Free loaded font
	TTF_CloseFont(font);
	font = NULL;

	// Free the music
	Mix_FreeMusic(backgroundMusic);
	backgroundMusic = NULL;

	// Free the sound effects
	Mix_FreeChunk(fallSound);
	Mix_FreeChunk(playerSound);
	fallSound = NULL;
	playerSound = NULL;
}

bool Level::loadMedia()
{
	// Loading success flag
	bool success = true;

	// Load background image
	backgroundTexture = util::loadTexture(renderer, backgroundTexturePath);
	if (backgroundTexture == NULL)
	{
		std::cout << "Failed to load texture image!" << std::endl;
		success = false;
	}

	// Load HUD overlay
	HUDTexture = util::loadTexture(renderer, HUDTexturePath);
	if (HUDTexture == NULL)
	{
		std::cout << "Failed to load texture image!" << std::endl;
		success = false;
	}

	// Load the font
	font = TTF_OpenFont("UI/Fonts/p5hatty.ttf", 48);
	if (font == NULL)
	{
		std::cout << "Failed to load font! SDL_Error: " << TTF_GetError() << std::endl;
		success = false;
	}

	// Load the background music
	backgroundMusic = Mix_LoadMUS(backgroundMusicPath.c_str());
	if (backgroundMusic == NULL)
	{
		std::cout << "Failed to load background music!" << std::endl;
		success = false;
	}

	// Load the sound effects
	fallSound = Mix_LoadWAV("Audio/SFX/zapsplat-error.wav");
	playerSound = Mix_LoadWAV("Audio/SFX/zapsplat-bounce.wav");

	// Load media for the menus
	pauseMenu->loadMedia();
	loseEndLevelMenu->loadMedia();
	winEndLevelMenu->loadMedia();

	return success;
}

void Level::update(float deltaTime)
{
	// If there is no music playing
	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(backgroundMusic, -1);
	}

	// Render background texture to screen
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	// Render HUD texture to screen
	SDL_RenderCopy(renderer, HUDTexture, NULL, NULL);
	
	// Draw level name on the HUD
	SDL_Color white = { 250, 250, 250 };
	util::Position namePosition = { 484.f - static_cast<int>(name.size()) * 12.f, 688.f };
	util::drawText(renderer, font, white, name.c_str(), namePosition, util::ParagraphFontSize);

	// Draw player score on the HUD
	SDL_Color cyan = { 0, 255, 225 };
	util::Position scorePosition = { 96.f, 735.f };
	util::drawText(renderer, font, cyan, std::to_string(player->getCurrentScore()).c_str(), scorePosition, util::ParagraphFontSize);

	// Draw player lives on the HUD
	SDL_Color red = { 255, 0, 84 };
	util::Position livesPosition = { 990.f, 735.f };
	util::drawText(renderer, font, red, std::to_string(player->getCurrentLives()).c_str(), livesPosition, util::ParagraphFontSize);

	// Draw the player
	currentPlayerPosition.x = util::clamp(currentPlayerPosition.x + player->getVelocity() * deltaTime, 0.f, 1024.f - 100.f);
	// Player is right next to a left wall -> stop accelerating
	if (currentPlayerPosition.x == 0.f)
	{
		player->turnOffAcceleration();
	}
	// Player is right next to a right wall -> stop accelerating
	if (currentPlayerPosition.x == 1024.f - 100.f)
	{
		player->turnOffAcceleration();
	}
	player->screenPosition = currentPlayerPosition;
	player->render();

	// Level is paused or just ended -> just draw the ball and bricks without updating it's location and without collision checks
	if (levelState == LevelState::Paused || levelState == LevelState::WinEndMenu || levelState == LevelState::LoseEndMenu)
	{
		// Draw the ball
		ball->render();

		// Draw the bricks
		for (int row = 0; row < static_cast<int>(bricksLayout.size()); row++)
		{
			for (int col = 0; col < static_cast<int>(bricksLayout.at(row).size()); col++)
			{
				Brick* brick = bricksLayout.at(row).at(col);
				if (brick->getIsEmpty())
				{
					continue;
				}
				if (brick->getIsCrushed())
				{
					continue;
				}
				brick->screenPosition = bricksPositions.at(row).at(col);
				brick->render(bricksWidthFactor, bricksHeightFactor);
			}
		}

		// Draw menu overlay background
		SDL_Rect fillRect = { 0, 0, 1024, 768 };
		SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x33); // Black with lowered alpha channel to get dimmed effect
		SDL_RenderFillRect(renderer, &fillRect);

		// Level is paused
		if (levelState == LevelState::Paused)
		{
			// Draw pause text
			util::drawText(renderer, font, white, "PAUSED", { 425.f, 150.f }, util::HeadingFontSize);

			// Draw pause menu
			pauseMenu->update(deltaTime);
		}
		// Level has ended in victory
		else if (levelState == LevelState::WinEndMenu)
		{
			// Draw victory text
			util::drawText(renderer, font, white, "VICTORY", { 425.f, 150.f }, util::HeadingFontSize);

			// Draw win end level menu
			winEndLevelMenu->update(deltaTime);
		}
		// Level has ended in loss
		else if (levelState == LevelState::LoseEndMenu)
		{
			// Draw loss text
			util::drawText(renderer, font, white, "DEFEAT", { 425.f, 150.f }, util::HeadingFontSize);

			// Draw lose end level menu
			loseEndLevelMenu->update(deltaTime);
		}

		return;
	}

	// Draw the ball
	currentBallPosition.x = util::clamp(currentBallPosition.x + currentBallDirectionX * (float)ball->getVelocity() * deltaTime, 0.f, 1024.f - 20.f);
	currentBallPosition.y = util::clamp(currentBallPosition.y + currentBallDirectionY * (float)ball->getVelocity() * deltaTime, 0.f, 768.f - 50.f);
	ball->screenPosition = currentBallPosition;
	ball->render();

	// Update ball upon a collision (bounce off)
	if (ball->hasHitWall())
	{
		// Ball hit bounding box -> bounce off by simple invert
		Ball::WallHit wallHit = ball->getPreviousWallHit();
		switch (wallHit)
		{
		case Ball::WallHit::Horizontal:
			currentBallDirectionX *= -1.f;
			break;
		case Ball::WallHit::Vertical:
			currentBallDirectionY *= -1.f;
			break;
		default:
			break;
		}
	}
	if (ball->hasFellDown())
	{
		// Play the sound effect
		Mix_PlayChannel(-1, fallSound, 0);
		// Ball fell down off the screen -> reposition at the start
		currentBallPosition = { 485.f, 618.f };
		currentBallDirectionX = 1.f;
		currentBallDirectionY = -1.f;
		// Reduce 1 life point to the player
		player->reduceLives();
		// End the level if the player lost all of his lives
		if (player->getCurrentLives() == 0)
		{
			player->turnOffAcceleration();
			levelState = LevelState::LoseEndMenu;
			loseEndLevelMenu->show();
		}
	}
	if (ball->isInCollisionWith(player))
	{
		// Play the sound effect
		Mix_PlayChannel(-1, playerSound, 0);
		// Ball hits the player -> bounce off by simple invert
		currentBallDirectionY = -1.f;
		// Ball hits the player in movement -> bounce off in the way of the movement
		if (std::abs(player->getVelocity()) >= 0.25f) 
		{
			currentBallDirectionX = player->getVelocity() >= 0 ? 1.f : -1.f;
		}
		// Ball hits the very edge of the player -> bounce off in the way of the edge
		else if (player->getHorizontalHitPosition() == GameObject::HitPosition::LeftEdge)
		{
			currentBallDirectionX = -1.f;
		}
		else if (player->getHorizontalHitPosition() == GameObject::HitPosition::RightEdge)
		{
			currentBallDirectionX = 1.f;
		}
	}

	// Draw bricks
	int numberOfRemainingBricks = 0;
	for (int row = 0; row < static_cast<int>(bricksLayout.size()); row++)
	{
		for (int col = 0; col < static_cast<int>(bricksLayout.at(row).size()); col++)
		{
			Brick* brick = bricksLayout.at(row).at(col);
			if (brick->getIsEmpty())
			{
				continue;
			}
			if (brick->getIsCrushed())
			{
				continue;
			}
			if (brick->isInCollisionWith(ball))
			{
				// Check if the flag was already set -> that means the brick and the ball are colliding for some time
				// If the flag is NOT set, calculate this as a valid hit and set the flag
				if (!brick->isInCollisionWithBall)
				{
					brick->isInCollisionWithBall = true;
					brick->hit();
				}
				if (brick->getVerticalHitPosition() == GameObject::HitPosition::Bottom)
				{
					currentBallDirectionY = 1.f;
				}
				else if (brick->getVerticalHitPosition() == GameObject::HitPosition::Top)
				{
					currentBallDirectionY = -1.f;
				}

				if (brick->getIsCrushed())
				{
					player->addToScore(brick->getBreakScore());
					continue;
				}
			}
			else 
			{
				brick->isInCollisionWithBall = false;
			}
			brick->screenPosition = bricksPositions.at(row).at(col);
			brick->render(bricksWidthFactor, bricksHeightFactor);
			if (brick->isBreakable())
			{
				numberOfRemainingBricks++;
			}
		}
	}
	if (numberOfRemainingBricks == 0)
	{
		player->turnOffAcceleration();
		levelState = LevelState::WinEndMenu;
		winEndLevelMenu->show();
	}
}

void Level::handleInput(SDL_Event* e)
{
	// Let pause menu handle the input
	if (levelState == LevelState::Paused)
	{
		pauseMenu->handleInput(e);

		if (pauseMenu->hasRequestedQuit())
		{
			levelState = LevelState::Quit;
		}

		return;
	}
	else {
		// Set the music to maximum outside of the pause menu
		Mix_VolumeMusic(MIX_MAX_VOLUME);
	}

	// Let lose end level menu handle the input
	if (levelState == LevelState::LoseEndMenu)
	{
		loseEndLevelMenu->handleInput(e);

		if (loseEndLevelMenu->hasRequestedQuit())
		{
			levelState = LevelState::Quit;
		}

		return;
	}

	// Let win end level menu handle the input
	if (levelState == LevelState::WinEndMenu)
	{
		winEndLevelMenu->handleInput(e);

		if (winEndLevelMenu->hasRequestedQuit())
		{
			levelState = LevelState::Quit;
		}

		return;
	}

	// Handle events on the queue
	while (SDL_PollEvent(e) != 0)
	{
		// User request quit
		if (e->type == SDL_QUIT) {
			levelState = LevelState::Quit;
		}
		// User presses a key
		if (e->type == SDL_KEYDOWN)
		{
			switch (e->key.keysym.sym)
			{
			case SDLK_ESCAPE:
				levelState = LevelState::Paused;
				pauseMenu->show();
				player->turnOffAcceleration();
				// Lower down the music in the pause menu
				Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
				break;
			case SDLK_LEFT:
				player->increaseAcceleration(true);
				break;
			case SDLK_RIGHT:
				player->increaseAcceleration(false);
				break;
			default:
				break;
			}
		}
		// User releases a key
		if (e->type == SDL_KEYUP)
		{
			switch (e->key.keysym.sym)
			{
			case SDLK_LEFT:
				player->turnOffAcceleration();
				break;
			case SDLK_RIGHT:
				player->turnOffAcceleration();
				break;
			default:
				break;
			}
		}
	}
}

bool Level::hasEnded()
{
	return levelState == LevelState::End;
}

bool Level::hasRequestedQuit()
{
	return levelState == LevelState::Quit;
}

bool Level::hasRequestedMainMenu()
{
	return levelState == LevelState::MainMenu;
}

void Level::resume()
{
	levelState = LevelState::Playing;
	pauseMenu->reset();
}

void Level::retry()
{
	// Reset all of the bricks properties
	for (int row = 0; row < static_cast<int>(bricksLayout.size()); row++)
	{
		for (int col = 0; col < static_cast<int>(bricksLayout.at(row).size()); col++)
		{
			Brick* brick = bricksLayout.at(row).at(col);
			brick->reset();
		}
	}

	// Reset player properties
	player->reset();
	currentPlayerPosition = { 445.f, 660.f }; // Initial player location

	// Reset ball properties
	currentBallDirectionX = 1.f;
	currentBallDirectionY = -1.f;
	currentBallPosition = { 485.f, 618.f }; // Initial ball location

	levelState = LevelState::Playing;
	pauseMenu->reset();
	loseEndLevelMenu->reset();
}

void Level::quit()
{
	levelState = LevelState::MainMenu;
}

void Level::end()
{
	levelState = LevelState::End;
}
