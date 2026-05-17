#ifndef CONSOLERPG_PLAYER_H
#define CONSOLERPG_PLAYER_H

#include <string>
#include "Inventory.h"

class Player
{
private:
    std::string name;
    int health;
    int maxHealth;
    int attackPower;
    Inventory inventory;

public:
    Player();

    Player(std::string name, int health, int attackPower, int capacity);

    ~Player();

    void takeDamage(int damage);

    std::string getName() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getAttackPower() const;

    void displayStatus() const;

    void showInventory() const;

    void addItem(const Item& item);
};

#endif //CONSOLERPG_PLAYER_H
