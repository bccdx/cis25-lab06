#include "Player.h"
#include <iostream>
using namespace std;

//default constructor
Player::Player(): name("Hero"), health(100), maxHealth(100), attackPower(10), inventory(5)
{
    cout << "Default constructor called for Player." << endl;
}

//overloaded constructor
Player::Player(string name, int health, int attackPower, int capacity): name(name), health(health), maxHealth(health), attackPower(attackPower), inventory(capacity)
{
    cout << "Overloaded constructor called for Player." << endl;
}

//destructor
Player::~Player()
{
    cout << "Player " << name << " has been destroyed." << endl;
}

//takeDamage function
void Player::takeDamage(int damage)
{
    health -= damage;

    //make sure health doesn't go below 0
    if (health < 0)
    {
        health = 0;
    }

    //player is defeated
    if (health == 0)
    {
        cout << name << " falls to the ground, defeated." << endl;
    }
}

//getter functions
string Player::getName() const
{
    return name;
}

int Player::getHealth() const
{
    return health;
}

int Player::getMaxHealth() const
{
    return maxHealth;
}

int Player::getAttackPower() const
{
    return attackPower;
}

//displayStatus function
void Player::displayStatus() const
{
    cout << name << " - HP: " << health << "/" << maxHealth << endl;
}

void Player::showInventory() const
{
    inventory.display();
}

void Player::addItem(const Item &item)
{
    inventory.addItem(item);
    cout << name << " found a ";
    item.display();
    cout << endl;
}
