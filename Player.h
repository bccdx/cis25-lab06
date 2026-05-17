#ifndef CONSOLERPG_PLAYER_H
#define CONSOLERPG_PLAYER_H

#include <string>

class Player
{
private:
    std::string name;
    int health;
    int maxHealth;
    int attackPower;

public:
    Player();

    Player(std::string name, int health, int attackPower);

    ~Player();

    void takeDamage(int damage);

    std::string getName() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getAttackPower() const;

    void displayStatus() const;
};

#endif //CONSOLERPG_PLAYER_H
