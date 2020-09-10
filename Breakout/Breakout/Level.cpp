#include "Level.h"

Level::Level(std::string path, SDL_Renderer* _renderer, Player* _player, std::string _name, bool _isRetryable) : 
	renderer(_renderer), player(_player), name(_name), isRetryable(_isRetryable)
{
	// Initialize ball for the level
	ball = new Ball(renderer);

	// Initialize pause menu
	if (isRetryable)
	{
		pauseMenu = new Menu<Level>(retryablePauseMenuButtons, renderer, retryablePauseMenuRequests, this);
	} 
	else
	{
		pauseMenu = new Menu<Level>(nonRetryablePauseMenuButtons, renderer, nonRetryablePauseMenuRequests, this);
	}

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
							float x = firstBrickPosition.x + col * (50.f + columnSpacing) / bricksWidthFactor;
							float y = firstBrickPosition.y + row * (20.f + rowSpacing) / bricksHeightFactor;
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
	// Free loaded images
	SDL_DestroyTexture(backgroundTexture);
	backgroundTexture = NULL;
	SDL_DestroyTexture(HUDTexture);
	HUDTexture = NULL;

	// Free loaded font
	TTF_CloseFont(font);
	font = NULL;
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

	// Load media for the pause menu
	pauseMenu->loadMedia();

	return success;
}

void Level::update()
{
	// Render background texture to screen
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	// Render HUD texture to screen
	SDL_RenderCopy(renderer, HUDTexture, NULL, NULL);
	
	// Draw level name on the HUD
	SDL_Color white = { 250, 250, 250 };
	util::Position namePosition = { 484.f - static_cast<int>(name.size()) * 12.f, 688.f };
	util::drawText(renderer, font, white, name.c_str(), namePosition, util::PARAGRAPH_FONT_SIZE);

	// Draw player score on the HUD
	SDL_Color cyan = { 0, 255, 225 };
	util::Position scorePosition = { 96.f, 735.f };
	util::drawText(renderer, font, cyan, std::to_string(player->getCurrentScore()).c_str(), scorePosition, util::PARAGRAPH_FONT_SIZE);

	// Draw player lives on the HUD
	SDL_Color red = { 255, 0, 84 };
	util::Position livesPosition = { 990.f, 735.f };
	util::drawText(renderer, font, red, std::to_string(player->getCurrentLives()).c_str(), livesPosition, util::PARAGRAPH_FONT_SIZE);

	// Draw the player
	player->render(currentPlayerPosition);

	// Level is paused -> just draw the ball and bricks without updating it's location and without collision checks
	if (levelState == LevelState::Paused)
	{
		// Draw the ball
		ball->render(currentBallPosition);

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
				util::Position brickPosition = bricksPositions.at(row).at(col);
				brick->render(brickPosition, bricksWidthFactor, bricksHeightFactor);
			}
		}

		// Draw pause overlay background
		SDL_Rect fillRect = { 0, 0, 1024, 768 };
		SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x33);
		SDL_RenderFillRect(renderer, &fillRect);

		// Draw pause text
		util::drawText(renderer, font, white, "PAUSED", {425.f, 150.f}, util::HEADING_FONT_SIZE);

		// Draw pause menu
		pauseMenu->update();

		return;
	}

	// Draw the ball
	currentBallPosition.x = util::clamp(currentBallPosition.x + currentBallDirectionX * (float)ball->getVelocity(), 0.f, 1024.f - 20.f);
	currentBallPosition.y = util::clamp(currentBallPosition.y + currentBallDirectionY * (float)ball->getVelocity(), 0.f, 768.f - 50.f);
	ball->render(currentBallPosition);

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
		// Ball fell down off the screen -> reposition at the start
		currentBallPosition = { 485.f, 618.f };
		// TODO: Randomize this direction
		currentBallDirectionX = 1.f;
		currentBallDirectionY = -1.f;
		// Reduce 1 life point to the player
		player->reduceLives();
	}
	if (ball->isInCollisionWith(player))
	{
		// Ball hits the player -> bounce off by simple invert
		currentBallDirectionY = -1.f;
		// Ball hits the player in movement -> bounce off in the way of the movement
		if (std::abs(player->getVelocity()) >= 10.f) 
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
				brick->hit();
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
			util::Position brickPosition = bricksPositions.at(row).at(col);
			brick->render(brickPosition, bricksWidthFactor, bricksHeightFactor);
			if (brick->isBreakable())
			{
				numberOfRemainingBricks++;
			}
		}
	}
	if (numberOfRemainingBricks == 0)
	{
		levelState = LevelState::End;
	}
}

void Level::handleInput(SDL_Event* e)
{
	if (levelState == LevelState::Paused)
	{
		pauseMenu->handleInput(e);

		if (pauseMenu->hasRequestedQuit())
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
				break;
			case SDLK_LEFT:
				player->increaseAcceleration(true);
				currentPlayerPosition.x = util::clamp(currentPlayerPosition.x + player->getVelocity(), 0.f, 1024.f - 100.f);
				if (currentPlayerPosition.x == 0.f)
				{
					// Player is right next to a wall -> stop accelerating
					player->turnOffAcceleration();
				}
				break;
			case SDLK_RIGHT:
				player->increaseAcceleration(false);
				currentPlayerPosition.x = util::clamp(currentPlayerPosition.x + player->getVelocity(), 0.f, 1024.f - 100.f);
				if (currentPlayerPosition.x == 1024.f - 100.f)
				{
					// Player is right next to a wall -> stop accelerating
					player->turnOffAcceleration();
				}
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
	currentPlayerPosition = { 445.f, 660.f };

	// Reset ball properties
	currentBallDirectionX = 1.f;
	currentBallDirectionY = -1.f; // TODO: move this to Ball class
	currentBallPosition = { 485.f, 618.f };

	levelState = LevelState::Playing;
	pauseMenu->reset();
}

void Level::quit()
{
	levelState = LevelState::MainMenu;
}
