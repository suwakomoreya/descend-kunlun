# Descending Kunlun
A simple vertical scrolling key-collecting game.
---
Scattered around the mountains from top to bottom lies multiple hidden keys scattered by a mischiveous monkey. Collect these keys and reach the opened gates to beat the game
-
Controls:
A and D to move left and right. Same for left and right arrow keys.
W, space, or arrow up to jump.
Enter in the menu to select.
Escape to exit game or exit tutorial.

Features: 
- Savepoints (i lied they actually dont save theyre more like checkpoints)
- Spikes (avoid these!!!! theyll send you back to your checkpoint)
- Hidden jades (theyre hiding in the trees looking at you)

Libraries used:
Nlohmann json to parse map data
Raylib library 

Compilation:

Have some sort of C++ compiler, and make sure youre using C++ 17+. (im using c++20) (this is on macos btw)
Cd to the directory of the games folder
run this command (youll need raylib installed first, e.g. `brew install raylib`):
 /usr/bin/clang++ src/main.cpp src/collision.cpp src/terrain.cpp -o game -std=c++17 -Wall -I. -I/opt/homebrew/include -L/opt/homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
Run the compiled game in your folder
#enjoy
