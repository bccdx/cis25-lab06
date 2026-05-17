#ifndef CONSOLERPG_ITEM_H
#define CONSOLERPG_ITEM_H

#include <string>

class Item
{
private:
    static int totalItems;
    std::string name;
    int value;

public:
    Item(std::string name = "Scrap", int value = 0);

    static int getTotalItems();
    static void incrementTotalItems();

    std::string getName() const;
    int getValue() const;

    void display() const;
};

#endif //CONSOLERPG_ITEM_H