#include "Map.h"
#include <iostream>
using namespace std;

//constructor
Map::Map(int width, int height, Player *player): width(width), height(height), playerPtr(player) {
    playerPtr->setX(1);
    playerPtr->setY(1);

    //create dynamic array of row pointers
    grid = new char*[height];

    //for each row, allocate a dynamic array
    for (int i = 0; i < height; i++)
    {
        grid[i] = new char[width];
    }

    //initialize
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            //initialize borders to #, otherwise .
            if (r == 0 || r == height - 1 || c == 0 || c == width - 1)
            {
                grid[r][c] = '#';
            }
            else
            {
                grid[r][c] = '.';
            }
        }
    }
}

Map::~Map()
{
    //first, delete each row
    for (int i = 0; i < height; i++)
    {
        delete[] grid[i];
    }

    //second, delete the array of row pointers
    delete[] grid;
}

int Map::getWidth() const
{
    return width;
}

int Map::getHeight() const
{
    return height;
}

void Map::draw() const
{
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            if (r == playerPtr->getY() && c == playerPtr->getX())
            {
                //draw the player
                cout << '@';
            }
            else
            {
                //draw everything else
                cout << grid[r][c];
            }
        }
        cout << endl;
    }
}

bool Map::isWall(int x, int y) const
{
    //is out of bounds
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        return true;
    }

    //is actual wall
    if (grid[y][x] == '#')
    {
        return true;
    }

    return false;
}