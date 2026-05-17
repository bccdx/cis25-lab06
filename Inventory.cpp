#include "Inventory.h"
#include <iostream>
using namespace std;

//constructor
Inventory::Inventory(int capacity): items(new Item[capacity]), capacity(capacity), itemCount(0)
{
    // constructor body (empty – all work done in init list)
}


//destructor
Inventory::~Inventory()
{
    delete[] items;
    cout << "Inventory has been destroyed." << endl;
}

//addItem function
bool Inventory::addItem(const Item& item)
{
    if (itemCount >= capacity) {
        //inventory full, so return false
        return false;
    }

    //add item
    items[itemCount] = item;

    //increment count
    itemCount++;

    //call incrementTotalItems
    Item::incrementTotalItems();

    //print message
    cout << "An item was added: " << item.getName() << endl;

    //return true since it's a success
    return true;
}

//display function
void Inventory::display() const
{
    cout << "Inventory (" << itemCount << "/" << capacity << "):" << endl;

    for (int i = 0; i < itemCount; i++) {
        cout << "  ";
        items[i].display();
        cout << endl;
    }
}