#include <iostream>
#include "Player.h"
#include "Game.h"

using namespace std;

int main()
{
    try
    {
        Game game;
        game.run();
    }
    catch (const std::exception& ex)
    {
        cout << "There was an exception!" << endl;
        cout << ex.what() << endl;
    }

    return 0;
}