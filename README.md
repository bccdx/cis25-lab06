# CIS 25 – Lab 7: Console RPG (Part 2)

## Objective

This lab continues our RPG project by building a dynamic inventory system. You will apply advanced C++ class features, including static members, class aggregation to give your Player an inventory, and a destructor to manage dynamic memory correctly.

## Before You Begin

Please make sure you have made a commit in your old repository with all of your previous work.

## Part 1: The Item Class (10 points)

First, we need a blueprint for all the items in our game world.

1. **Create the Files**: In your `ConsoleRPG` project, create `Item.h` and `Item.cpp`.
2. **Define the `Item` Class**:
   - In `Item.h`, create a class named `Item`.
   - Add a private static `int` member variable named `totalItems` to track how many items have been added to inventories.
   - Add private instance members: `name` (string) and `value` (int).
   - Add a public constructor with the signature `Item(std::string name = "Scrap", int value = 0);`
   - Add a public static member function with the signature `static int getTotalItems();`
   - Add a public static member function with the signature `static void incrementTotalItems();` This will allow the `Inventory` class to update the counter when an item is added.
   - Add accessor (getter) functions for `name` and `value`. These must be marked as `const`.
   - Add a public method to display the item with the signature `void display() const;` It should print the item in the format: `[Name] (Value: [Value])`

3. **Implement the `Item` Class**:
   - In `Item.cpp`, define and initialize `static int Item::totalItems` to `0`.
   - Implement your constructor using a **member initialization list** to initialize `name` and `value` from the parameters.

     **Member Initialization List**: Instead of assigning to member variables inside the constructor body, use the initialization list syntax after the constructor signature:

     ```cpp
     Item::Item(std::string name, int value)
         : name(name), value(value)   // <-- initialization list
     {
         // constructor body (empty for now)
     }
     ```

     This is more efficient because it initializes the members directly rather than default-constructing them first and then reassigning. For `std::string` in particular, it avoids creating an empty string and then copying over it.

   - Implement the `getTotalItems` and `incrementTotalItems` functions.
   - Implement the `display` function.

## Part 2: The Inventory Class (15 points)

This class will manage a collection of items using dynamic memory.

1. **Create the Files**: Create `Inventory.h` and `Inventory.cpp`.
2. **Define the `Inventory` Class**:
   - In `Inventory.h`, create a class named `Inventory`.
   - Add private members: `items` (a pointer to an `Item` array), `capacity` (an `int`), and `itemCount` (an `int`).
   - Add a public constructor with the signature `Inventory(int capacity);`
   - Add a destructor with the signature `~Inventory();`
   - Add a method to add an item with the signature `bool addItem(const Item& item);`
   - Add a method to display the inventory with the signature `void display() const;`

3. **Implement the `Inventory` Class**:
   - In `Inventory.cpp`, implement all the declared functions.
   - Your constructor should use a **member initialization list** to initialize `capacity` and `itemCount` (to `0`), and dynamically allocate the `items` array.

     **Member Initialization List**: You can initialize all three members in the list, including the dynamic allocation with `new`:

     ```cpp
     Inventory::Inventory(int capacity)
         : items(new Item[capacity]),
           capacity(capacity),
           itemCount(0)
     {
         // constructor body (empty – all work done in init list)
     }
     ```

     Since `new` is an expression that returns a pointer, it works in the initialization list just like any other value.

   - Your **destructor** must free the dynamically allocated memory.
   - `addItem` should add an item if there is capacity, returning `true` on success and `false` if the inventory is full. On success, it should also call `Item::incrementTotalItems()` and print a message like `"An item was added: [Name]"`. It should also increment the `itemCount` on the `Inventory`.

## Part 3: Aggregation in Player (10 points)

Now, we will modify the `Player` class to integrate the `Inventory`.

1. **Modify the `Player` Class**:
   - In `Player.h`, `#include "Inventory.h"` and add a private member variable: `inventory` (an `Inventory` object).
   - Add a new public method to display the inventory with the signature `void showInventory() const;`
   - Add a new public method to add an item with the signature `void addItem(const Item& item);`

2. **Implement the New Player Functions**:
   - In `Player.cpp`, implement the `showInventory` function. It should call the `Inventory`’s `display` method.
   - Update your `Player` constructor to use a **member initialization list** that passes a capacity value to the `inventory` member. Since `Inventory` has no default constructor (it requires a `capacity` argument), the initialization list is required here—the code will not compile without it:

     ```cpp
     Player::Player(std::string name, int health)
         : name(name), health(health), inventory(10)
     {
         cout << "Default constructor called for Player." << endl;
     }
     ```

     This is the key example of **class aggregation**: when one class contains another as a member, the outer class’s constructor must initialize the inner object via the initialization list. If the inner class has no default constructor, the initialization list is the only way to construct it.

   - Implement the `addItem` function. It should call the `Inventory`’s `addItem` method.

## Part 4: The Game Engine (main.cpp) (5 points)

Update your `main` function to test all the new features.

1. Create a `Player` object named `hero`.
2. Create several `Item` objects, including at least one that will **not** be added to the player’s inventory.
3. Add items to the `hero`’s inventory using the `Player`’s `addItem` method.
4. Display the `hero`’s inventory.
5. Test the static member by printing the total number of items created using `Item::getTotalItems()`.

## Sample Interaction

```
Default constructor called for Player.

--- Adding items to hero's inventory ---
An item was added: Sword
Hero found a [Sword] (Value: 10)
An item was added: Shield
Hero found a [Shield] (Value: 15)

--- Hero's Inventory ---
Inventory (2/5):
  [Sword] (Value: 10)
  [Shield] (Value: 15)

Total items added to inventories: 2

Player Hero has been destroyed.
Inventory for Hero has been destroyed.
```

## Submission Guidelines

- You will submit the **SAME Git repository** as last time, but with the updated code.
- Make a commit with all the work from Part 2.
- Make sure your program **compiles and runs** without errors.
