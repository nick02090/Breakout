#include "LevelGenerator.h"
#include <stdlib.h>
#include <time.h>

LevelGenerator::LevelGenerator(SDL_Renderer* _renderer) : renderer(_renderer)
{
    // Initialize all brick types
    Brick* softBrick = new Brick(renderer, "SoftBrick", "S", "GameObjects/SoftBrick.png", 1, 
        "Audio/SFX/zapsplat-collect3.wav", "Audio/SFX/zapsplat-break.wav", 50);
    Brick* mediumBrick = new Brick(renderer, "MediumBrick", "M", "GameObjects/MediumBrick.png", 2,
        "Audio/SFX/zapsplat-collect2.wav", "Audio/SFX/zapsplat-break.wav", 100);
    Brick* hardBrick = new Brick(renderer, "HardBrick", "H", "GameObjects/HardBrick.png", 3,
        "Audio/SFX/zapsplat-collect1.wav", "Audio/SFX/zapsplat-break.wav", 150);
    Brick* impenetrableBrick = new Brick(renderer, "ImpenetrableBrick", "I", "GameObjects/ImpenetrableBrick.png", 0,
        "Audio/SFX/zapsplat-collect4.wav", "", 0);
    Brick* emptyBrick = new Brick(_renderer, "EmptyBrick", "_");
    // Add them to the bricks
    bricks.push_back(softBrick);
    bricks.push_back(mediumBrick);
    bricks.push_back(hardBrick);
    bricks.push_back(impenetrableBrick);
    bricks.push_back(emptyBrick);
}

LevelGenerator::~LevelGenerator()
{
}

Level* LevelGenerator::generate(Player* player)
{
    // New seed
    srand((unsigned int)time(NULL));
    // Random texture and soundtrack
    int randomTextureIndex = rand() % 3;
    std::string backroundTexturePath = BackgroundTexturesPath[randomTextureIndex];
    int randomMusicIndex = rand() % 8;
    std::string backgroundMusicPath = BackgroundMusicPath[randomMusicIndex];
    int randomNameIndex = randomTextureIndex;
    std::string name = LevelNames[randomNameIndex];
    // Random brick grid size
    int rowCount = MinRowCount + (rand() % (MaxRowCount - MinRowCount + 1));
    int columnCount = MinColumnCount + (rand() % (MaxColumnCount - MinColumnCount + 1));
    int spacing = MinSpacing + (rand() % (MaxSpacing - MinSpacing + 1));
    int rowSpacing = spacing;
    int columnSpacing = spacing;
    // Calculate bricks screen factors
    float neededBrickWidth = columnCount * BrickWidth + (columnCount - 1) * rowSpacing;
    float neededBrickHeight = rowCount * BrickHeight + (rowCount - 1) * columnSpacing;
    float bricksWidthFactor = neededBrickWidth / MaxBricksWidth;
    float bricksHeightFactor = neededBrickHeight / MaxBricksHeight;
    // Random brick layout
    std::vector<std::vector<Brick*>> bricksLayout;
    std::vector<std::vector<util::Position>> bricksPositions;

    util::Position firstBrickPosition = { 10.f, 10.f };
    int rows = MinRows + (rand() % (MaxRows - MinRows + 1));
    int cols = columnCount;
    // Maximum number of impenetrables should be less than a number of bricks that fit in one row
    int impenetrablesPerGrid = cols / 2;
    int impenetrablesCount = 0;
    std::vector<Brick*> bricksRow;
    std::vector<util::Position> bricksRowPositions;
    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            int randomBrickIndex = rand() % 5;
            Brick* randomBrick = bricks.at(randomBrickIndex);
            if (randomBrick->getId()._Equal("I"))
            {
                // All the impenetrables are already put on the grid
                if (impenetrablesCount >= impenetrablesPerGrid)
                {
                    // Put a soft brick instead
                    randomBrick = bricks.at(0);
                }
                // Put impenetrables only on every second row so they don't close up space
                else if (row % 2 == 0)
                {
                    // Put a soft brick instead
                    randomBrick = bricks.at(0);
                }
                else 
                {
                    impenetrablesCount++;
                }
            }
            float x = firstBrickPosition.x + col * (BrickWidth + columnSpacing) / bricksWidthFactor;
            float y = firstBrickPosition.y + row * (BrickHeight + rowSpacing) / bricksHeightFactor;
            if (randomBrick->getIsEmpty())
            {
                bricksRow.push_back(new Brick(renderer, "EmptyBrick", "_"));
            }
            else
            {
                bricksRow.push_back(new Brick(randomBrick));
            }
            bricksRowPositions.push_back({ x, y });
        }
    }
    bricksPositions.push_back(bricksRowPositions);
    bricksLayout.push_back(bricksRow);

    return new Level(renderer, player, name, rowCount, columnCount, rowSpacing, columnSpacing, 
        backroundTexturePath, backgroundMusicPath, bricks, bricksLayout, bricksWidthFactor, 
        bricksHeightFactor, bricksPositions);
}

