#ifndef CONSOLERPG_GAME_H
#define CONSOLERPG_GAME_H

#include "Player.h"
#include "Map.h"

class Game
{
private:
    Player player;
    Map gameMap;
    bool running;

    void processInput();

public:
    Game();

    ~Game();

    void run();
};

#endif //CONSOLERPG_GAME_H
