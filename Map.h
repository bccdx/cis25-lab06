#ifndef CONSOLERPG_MAP_H
#define CONSOLERPG_MAP_H

#include "Player.h"

class Map
{
private:
    char** grid;
    int width;
    int height;
    Player* playerPtr;

public:
    Map(int width, int height, Player* player);

    ~Map();

    int getWidth() const;
    int getHeight() const;

    void draw() const;

    bool isWall(int x, int y) const;
};

#endif //CONSOLERPG_MAP_H
