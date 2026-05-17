#include "Player.h"
#include <iostream>
using namespace std;

//default constructor
Player::Player()
{
    name = "Hero";
    health = 100;
    maxHealth = 100;
    attackPower = 10;
    cout << "Default constructor called." << endl;
}

//overloaded constructor
Player::Player(string name, int health, int attackPower)
{
    this->name = name;
    this->health = health;
    this->maxHealth = health;
    this->attackPower = attackPower;
    cout << "Overloaded constructor called." << endl;
}

//destructor
Player::~Player()
{
    cout << "The object for Player " << name << " has been destroyed." << endl;
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