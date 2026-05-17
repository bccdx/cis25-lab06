# CIS 25 - Lab 6: Console RPG (Part 1)

## Objective

This is the first lab in a larger project to build a console-based Role-Playing Game (RPG). Today, you will lay the foundation by creating a `Player` class. The goal is to apply your understanding of object-oriented programming by defining a class, using access specifiers, implementing constructors and methods, and separating your code into specification and implementation files.

## Part 1: The Class Specification (Player.h)

Your first task is to define the "blueprint" for our `Player` object in a header file. This file will declare what a `Player` is and what it can do, without getting into the details of *how* it does it.

1. **Create a New Project**: Create a new project named `ConsoleRPG`.
2. **Create the Header File**: Inside your project, create a new C/C++ Header File named `Player.h`.
3. **Define the `Player` Class**: Inside `Player.h`, write the complete class definition. It must include:
   - An **include guard** (see the lecture notes for what this is)
   - **private members** (these are the internal attributes of the player):
     - `name` (a `std::string`)
     - `health` (an `int`)
     - `maxHealth` (an `int`)
     - `attackPower` (an `int`)
   - **public members** (Function Prototypes Only) — these are the actions the player can perform and the ways we can interact with it:
     - A default constructor: `Player();`
     - An overloaded constructor that accepts a name, health, and attack power: `Player(std::string name, int health, int attackPower);`
     - A destructor: `~Player();`
     - A method to inflict damage on the player: `void takeDamage(int damage);`
     - Accessor (getter) functions for each member variable. These must be marked as `const` (e.g., `std::string getName() const;`, `int getHealth() const;`, etc.).
     - A helper function to display the player's current status: `void displayStatus() const;`

## Part 2: The Class Implementation (Player.cpp)

Now you will write the definitions for all the member functions you declared in `Player.h`.

1. **Create the Implementation File**: In your project, create a new C/C++ Source File named `Player.cpp`.
2. **Implement the Functions**: Inside `Player.cpp`, you must:
   - `#include` the `Player.h` header file and any other necessary libraries like `<iostream>`.
   - Use the scope resolution operator `::` to define each function.
   - **Default Constructor**: Initialize the player with default stats: `name` `"Hero"`, `health` `100`, `maxHealth` `100`, and `attackPower` `10`.
   - **Overloaded Constructor**: Initialize the player's `name`, `health`, and `attackPower` with the provided parameter values. Set `maxHealth` to be equal to the starting health.
   - **Destructor**: Print a simple message, like `"The object for Player [name] has been destroyed."`.
   - **`takeDamage(int damage)`**: This function should subtract the `damage` amount from the player's `health`. Also:
     - Add logic to ensure health never drops below `0`.
     - Add logic to print `"[name] falls to the ground, defeated."` if taking damage brings the player's health to `0`.
   - **Getter Functions**: Each getter should simply return the value of its corresponding member variable.
   - **`displayStatus()` Function**: This function should print the player's current status to the console in a clean format, like: `"[Name] - HP: [health]/[maxHealth]"`.

## Part 3: The Game Engine (main.cpp)

Your `main` function will serve as the testbed for your `Player` class.

1. **Include Header**: Make sure to `#include "Player.h"` at the top of `main.cpp`.
2. **Create Player Objects**:
   - Create a `Player` object named `hero` using the default constructor.
   - Create another `Player` object named `wizard` using the overloaded constructor. Give the wizard a name of your choice, `120` health, and `15` attack power.
3. **Test the Methods**:
   - Display the initial status of both the `hero` and the `wizard` by calling their `displayStatus()` methods.
   - Simulate the `hero` taking `25` damage by calling the `takeDamage()` method.
   - Display the `hero`'s status again to confirm their health has changed.
   - Simulate the `wizard` taking a massive `150` damage hit.
   - Display the `wizard`'s status to confirm their health is `0` and not a negative number.

## Sample Output

Your final output should look very similar to this:
```
Default constructor called.
Overloaded constructor called.

--- Initial Status ---
[Hero] - HP: 100/100
[Gandalf] - HP: 120/120

--- Hero takes damage! ---
[Hero] - HP: 75/100

--- Wizard takes damage! ---
[Gandalf] - HP: 0/120

Gandalf falls to the ground, defeated.

The object for Player Gandalf has been destroyed.
The object for Player Hero has been destroyed.
```
## Submission Guidelines

1. As always, please submit a **Git repository**.
2. There should be **three separate files** in the repo: `Player.h`, `Player.cpp`, and `main.cpp`.
3. Ensure your code is **well-commented** and that your `Player` class is fully encapsulated (private data, public methods).
4. Make sure your program **compiles and runs** without errors.
