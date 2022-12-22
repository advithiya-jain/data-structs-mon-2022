___
# Data Structures Final Project - A Turn based game using Red-Black Trees
___

# Note: 
This project is also available on my [git repo here](https://github.com/advithiya-jain/data-structs-mon-2022/tree/main/Project). If for any reason code within the zip file does not work, please download the files from there.

## Implementations:
1. Red-Black trees (r-b_trees.c, rbtrees.h) with:
    * Insertion
    * Searching
    * Updating
2. "Dictionary" which is the Red-Black tree with keys and values mapped to them.
3. A working turn-based game (game.c, game_functions.c, gamefns.h) with a randomiser that uses the dictionary to keep track of player and enemy values. You will recieve all the instructions you need through the game to play/test it.

## Testing:

    Since the game has functionality for randomness, the only way to test was to provide user input. 
    
    In my testing I used all the items available until I lost or won. 
    
    All outputs were as expected and are outlined in the Tutorial portion of the game. 
    
    Deaths, Levelling up, damaging, and restoration are working correctly and as expected.

## How to run?
* The project uses 5 different files:
    - Three .c files and two header (.h) files.
* To run the project you must:
    1. Use a C compiler that allows multiple input files (preferably gcc)
    2. If using gcc, your command should be: 
    "``gcc -o project game.c r-b_trees.c game_functions.c``" If using any other compiler, make sure to use these three input files: "game.c", "r-b_trees.c", and "game_functions.c"
    3. Please make sure that the compiler is run in a folder which has all 5 files present.

If for any reason the header files are not being linked by the compiler, please change the following in the the files:
```#include "<headerfile.h>" should be changed to #include "<full path to headerfile.h>"```.

For example if the header files are located in a folder named 'Project' on the desktop in Windows, the line would be:
```#include "C:\Users\<username>\Desktop\Project\<headerfile.h>"```

This can be an issue on Windows, but in my testing I have used MacOS 13.0 with no such issues. 
