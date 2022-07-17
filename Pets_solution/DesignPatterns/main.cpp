// DesignPatterns.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Mediator.h"

int main()
{
    Game game;
    Player player{ "Kirk", game };
    Coach coach{ game };

    player.Score();
    player.Score();
    player.Score();
    player.Score();
}
