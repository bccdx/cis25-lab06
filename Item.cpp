#include "Item.h"
#include <iostream>
using namespace std;

int Item::totalItems = 0;

//constructor using member initialization list
Item::Item(std::string name, int value): name(name), value(value)
{
}

//getTotalItems function
int Item::getTotalItems()
{
    return totalItems;
}

//incrementTotalItems function
void Item::incrementTotalItems()
{
    totalItems++;
}

//getter functions
std::string Item::getName() const
{
    return name;
}

int Item::getValue() const
{
    return value;
}

//display function
void Item::display() const
{
    cout << "[" << name << "] (Value: " << value << ")";
}