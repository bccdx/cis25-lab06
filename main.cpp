#include <iostream>
#include "Player.h"

using namespace std;

int main()
{
    Player hero;
    Player wizard("Bruce", 120, 15);
    cout << endl;

    cout << "--- Initial Status ---" << endl;
    hero.displayStatus();
    wizard.displayStatus();
    cout << endl;

    cout << "--- Hero takes damage! ---" << endl;
    hero.takeDamage(25);
    hero.displayStatus();
    cout << endl;

    cout << "--- Wizard takes damage! ---" << endl;
    wizard.takeDamage(150);
    wizard.displayStatus();
    cout << endl;

    return 0;
}