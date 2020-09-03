// Breakout.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game.h"

int main(int argc, char* args[])
{
    std::cout << "Starting your game..." << std::endl;

    Game* game = new Game();
    game->start();

    std::cout << "Thank you for playing!" << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
