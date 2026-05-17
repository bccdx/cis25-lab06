# CIS 25 – Lab 8: Console RPG (Part 3)

## Objective

In this lab, you will build a dynamic game world for your console RPG. You will create a `Map` class that uses a dynamically allocated 2D array, and a `Game` class that ties your existing `Player`, `Inventory`, and `Item` classes together into a playable game with a main loop, movement, and collision detection.

This lab builds directly on your work from **Lab 6** (`Player` class) and **Lab 7** (`Item`, `Inventory`, and class aggregation). Your existing classes are assumed to be working and will not be re-graded here.

## Before You Begin

Make sure you have the following files from previous labs, all compiling and working correctly:

- `Player.h` / `Player.cpp` – Your `Player` class from Lab 6 (updated in Lab 7 to include an `Inventory` member)
- `Item.h` / `Item.cpp` – Your `Item` class from Lab 7
- `Inventory.h` / `Inventory.cpp` – Your `Inventory` class from Lab 7

Make a commit with your current work before starting this lab.

---

## Part 1: Update the Player Class (5 points)

Your `Player` class currently has a name, health, attack power, and an inventory. For this lab, the player also needs a position on the map. You will add **x** and **y** coordinates to the `Player` class.

### Step 1: Add Position Members to `Player.h`

Add the following private member variables to your `Player` class:

- `int x` – The player's horizontal position (column)
- `int y` – The player's vertical position (row)

Add the following public methods:

- `int getX() const` and `int getY() const`
- `void setX(int x)` and `void setY(int y)`

### Step 2: Initialize Position in the Constructor

Update your `Player` constructor's member initialization list to set `x` and `y` to `0`. The `Map` constructor will set the actual starting position later.

### A Note on Coordinates

Throughout this lab, we use the convention that **x is the column** (horizontal position) and **y is the row** (vertical position). When you access the grid, the pattern is `grid[y][x]` – row first, then column. This matches how a 2D array is laid out in memory (array of rows), but it means the order is the reverse of what you might expect.

To keep things straight:

- `grid[row][col] = grid[y][x]`
- Moving **up** decreases `y`; moving **down** increases `y`
- Moving **left** decreases `x`; moving **right** increases `x`

### Key Concept: Initialization Lists (Revisited)

You used member initialization lists in Lab 7 to construct the `Inventory` inside the `Player`. In this lab, the same technique is critical for the `Game` class, which owns both a `Player` and a `Map`. Here is a quick reminder of why this matters.

**Without an Initialization List (Inefficient)**

```cpp
Game::Game() {
    // By the time we get here, C++ has ALREADY called the
    // default constructors for player and gameMap.
    player = Player("Hero", 100, 10);  // Creates a SECOND Player,
                                        // then copies it over the first.
}
```

What actually happens:

1. `Player()` is called automatically (default constructor) before the body runs.
2. `Player("Hero", 100, 10)` creates a temporary second `Player`.
3. The assignment operator copies the temporary over the first `Player`.
4. The temporary is destroyed.

**Result:** Two `Player` objects are created when only one was needed.

**With an Initialization List (Correct)**

```cpp
Game::Game()
    : player("Hero", 100, 10),     // Construct player directly
      gameMap(30, 15, &player),     // Construct map directly
      running(true) {
    // Both objects are already fully constructed here.
}
```

What happens:

1. `Player("Hero", 100, 10)` is called directly. No default constructor needed.
2. `Map(30, 15, &player)` is called directly.
3. The constructor body runs with both objects ready to use.

**Result:** Only one `Player` and one `Map` are ever created. Efficient and correct.

---

## Part 2: Understanding Dynamic 2D Arrays

Your `Map` class will store its grid as a dynamically allocated 2D array. This section walks through the concept.

### Why Not a Static 2D Array?

A traditional 2D array requires the size to be known at compile time:

```cpp
char grid[5][3];  // 5 rows, 3 columns – fixed at compile time
```

But if the size is determined at runtime, standard C++ does not allow this:

```cpp
int height, width;
cin >> height >> width;
char grid[height][width];  // ERROR! Not valid in standard C++
```

To solve this, we use dynamic memory allocation with pointers.

### Creating a Dynamic 2D Array

The pattern has three steps:

**Step 1:** Create a dynamic array of row pointers.

```cpp
char** grid = new char*[height];  // 'height' pointers, one per row
```

**Step 2:** For each row, allocate a dynamic array.

```cpp
for (int i = 0; i < height; i++) {
    grid[i] = new char[width];    // Each row has 'width' chars
}
```

**Step 3:** Initialize the values.

```cpp
for (int r = 0; r < height; r++) {
    for (int c = 0; c < width; c++) {
        grid[r][c] = '.';
    }
}
```

After this, you can use `grid[r][c]` exactly like a normal 2D array.

### Cleaning Up a Dynamic 2D Array

Because you used `new` to allocate, you must use `delete[]` to free it. Cleanup happens in reverse order:

```cpp
// First: delete each row
for (int i = 0; i < height; i++) {
    delete[] grid[i];
}
// Second: delete the array of pointers
delete[] grid;
```

Failing to do this causes a **memory leak**. This cleanup belongs in your destructor.

---

## Part 3: The Map Class (20 points)

Now you will create a `Map` class that represents the game world as a bordered grid.

### Step 1: Create `Map.h`

Create a header file named `Map.h`. Define a `Map` class with the following:

**Private Members:**

- `char** grid` – A pointer-to-pointer for the dynamic 2D array
- `int width` – Number of columns
- `int height` – Number of rows
- `Player* playerPtr` – A pointer to the `Player` (so the map knows where to draw them)

**Public Methods:**

- A constructor: `Map(int width, int height, Player* player)`
- A destructor: `~Map()`
- `void draw() const` – Display the map to the console
- `bool isWall(int x, int y) const` – Check if a position is a wall or out of bounds
- Getter functions for `width` and `height`

### Step 2: Create `Map.cpp` and Implement the Constructor

Create `Map.cpp` and implement the constructor. It should:

- Store the `width`, `height`, and `player` pointer in the member variables.
- Set the player's starting position to `(1, 1)` using the player pointer. This places them just inside the top-left wall.
- Allocate the dynamic 2D array using the pattern from Part 2.
- Initialize the grid: cells on the border (first/last row, first/last column) should be `'#'` (wall). All other cells should be `'.'` (floor).

> **Hint:** A cell at row `r` and column `c` is on the border if `r == 0`, `r == height - 1`, `c == 0`, or `c == width - 1`.

### Step 3: Implement the Destructor

Your destructor must free all dynamically allocated memory in reverse order, exactly as described in Part 2. This is critical to prevent memory leaks.

### Step 4: Implement `draw()`

The `draw()` method should:

- Loop through every row (`r` from `0` to `height-1`) and column (`c` from `0` to `width-1`).
- If `c == playerPtr->getX()` and `r == playerPtr->getY()`, print `'@'` instead of the map tile.
- Otherwise, print the character stored in `grid[r][c]`.
- Print a newline at the end of each row.

> **Remember:** The grid is accessed as `grid[row][col]` which is `grid[y][x]`. The player's `x` is the column and `y` is the row.

### Step 5: Implement `isWall()`

The `isWall()` method should:

- Return `true` if the given `(x, y)` position is outside the map boundaries (less than 0 or greater than or equal to `width`/`height`).
- Return `true` if `grid[y][x]` is `'#'`.
- Return `false` otherwise.

---

## Part 4: The Game Class (10 points)

The `Game` class ties everything together. It owns the `Player` and the `Map`, runs the main game loop, and processes user input.

### Step 1: Create `Game.h`

Create a header file named `Game.h`. Define a `Game` class with the following:

**Private Members:**

- `Player player` – A `Player` object (not a pointer – the `Game` owns the player)
- `Map gameMap` – A `Map` object (the `Game` owns the map)
- `bool running` – A flag to control the game loop

> **Important:** Declare `player` **before** `gameMap` in your class definition. C++ initializes members in the order they are declared, not the order they appear in the initialization list. Since the `Map` constructor needs a pointer to the player, the player must be constructed first.

**Public Methods:**

- Constructor and destructor
- `void run()` – The main game loop

**Private Helper Methods:**

- `void processInput()` – Handle user keyboard commands

### Step 2: Implement the Constructor

You must use an **initialization list** (see the Key Concept section). Here is the structure to follow:

```cpp
Game::Game()
    : player("Hero", 100, 10),     // Name, health, attack power
      gameMap(30, 15, &player),     // Width, height, pointer to player
      running(true) {
 
    // Optional: give the player starting items
    player.addItem(Item("Sword", 10));
    player.addItem(Item("Shield", 5));
 
    // Display a welcome message
}
```

> **Note:** The map is initialized with `&player` (the address of the `Game`'s player member). This is safe because `player` is declared **before** `gameMap` in the class, so it is already constructed by the time the `Map` constructor runs.

### Step 3: Implement `run()`

The `run()` method is your main game loop. It should repeat the following while `running` is `true`:

- Clear the screen (you can print several blank lines, or use a system-specific clear command).
- Print a game title or header.
- Call `gameMap.draw()` to display the map.
- Display player stats (name, health, position).
- Call `processInput()` to handle the player's next command.

### Step 4: Implement `processInput()`

This method should:

- Read a single character from the user.
- Convert it to uppercase for consistency (use `toupper()`).
- Based on the character, calculate where the player wants to move:
  - `W` – Move up (decrease `y` by 1)
  - `S` – Move down (increase `y` by 1)
  - `A` – Move left (decrease `x` by 1)
  - `D` – Move right (increase `x` by 1)
  - `Q` – Quit the game (set `running` to `false`)
- Check if the target position is a wall using `gameMap.isWall(newX, newY)`.
- If it is **not** a wall, update the player's position using `setX()` and `setY()`.

---

## Part 5: Putting It All Together (`main.cpp`) (5 points)

Your `main.cpp` should be short and clean:

- Include the necessary headers (`Game.h` and `<iostream>`).
- In `main()`, create a `Game` object and call its `run()` method.
- Wrap the code in a try-catch block for basic error handling.

The entire `main()` function should be about 10 lines of code.

---

## Expected Behavior

When complete, your game should:

✓ Display a bordered map with walls (`#`) and floor (`.`)  
✓ Show the player (`@`) on the map at position (1, 1)  
✓ Allow WASD movement (input followed by Enter)  
✓ Prevent walking through walls  
✓ Display player stats (name, health, position)  
✓ Quit cleanly when the user presses Q  
✓ Clean up all dynamic memory with no leaks  

---

## Common Issues to Watch For

- **Segmentation faults:** Double-check your array bounds and make sure pointers are not null before dereferencing.
- **Memory leaks:** Ensure your `Map` destructor frees every row and then the array of pointers.
- **Player not appearing:** Make sure your `draw()` method compares the column loop variable to `getX()` and the row loop variable to `getY()`. Getting these swapped is the #1 cause of this bug.
- **Cannot move:** Check that your movement logic uses the correct signs. `W` (up) should decrease `y`, not increase it, because row 0 is the top of the screen.
- **Initialization order crash:** If `gameMap` is declared before `player` in your `Game` class, the `Map` will receive a pointer to an unconstructed `Player`. Always declare `player` first.
- **Input issues:** Standard `cin >>` waits for Enter. This is expected and fine for this lab.

---

## Submission Guidelines

- You will submit the **SAME Git repository** as previous labs, with the new and updated code.
- Your repository should contain the following files:
  - `Player.h` and `Player.cpp` (updated with position members)
  - `Item.h` and `Item.cpp`
  - `Inventory.h` and `Inventory.cpp`
  - `Map.h` and `Map.cpp` (new)
  - `Game.h` and `Game.cpp` (new)
  - `main.cpp` (updated)
- Ensure your code is well-commented and that all classes are properly encapsulated.
- Make sure your program **compiles and runs** without errors.
