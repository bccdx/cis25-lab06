#include "Game.h"
#include <iostream>
using namespace std;

Game::Game(): player("Hero", 100, 10, 5), gameMap(30, 15, &player), running(true)
{
    player.addItem(Item("Sword", 10));
    player.addItem(Item("Shield", 5));

    cout << "Welcome to the Game" << endl;
}

Game::~Game()
{

}

void Game::run()
{
    while (running)
    {
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "The Game" << endl;
        gameMap.draw();
        cout << endl;
        player.displayStatus();
        player.showInventory();
        cout << endl;
        processInput();
    }
}

void Game::processInput()
{
    //read a character
    char input;
    cin >> input;

    //covert it to uppercase
    input = toupper(input);

    int currentX = player.getX();
    int currentY = player.getY();

    if (input == 'W')
    {
        currentY -= 1;
    }
    else if (input == 'S')
    {
        currentY += 1;
    }
    else if (input == 'A')
    {
        currentX -= 1;
    }
    else if (input == 'D')
    {
        currentX += 1;
    }
    else if (input == 'Q')
    {
        //stop the game
        running = false;
    }

    //update the player position if it is valid
    if (!gameMap.isWall(currentX, currentY))
    {
        player.setX(currentX);
        player.setY(currentY);
    }
    else
    {
        cout << "You ran into a wall!" << endl;
    }
}
