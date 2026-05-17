#include <iostream>
#include "Player.h"

using namespace std;

int main()
{
    Player hero;

    cout << endl;

    Item sword("Sword", 10);
    Item shield("Shield", 15);
    Item belt("Belt", 5);

    cout << "--- Adding items to " << hero.getName() << "'s inventory ---" << endl;
    hero.addItem(sword);
    hero.addItem(shield);
    cout << endl;

    cout << "--- " << hero.getName() << "'s Inventory ---" << endl;
    hero.showInventory();
    cout << endl;

    cout << "Total items added to inventories: " << Item::getTotalItems() << endl;

    return 0;
}