# TechnicalGameDev
PLATFORM:
PC (Windows) + Dragonfly Engine (Thanks to Professor Claypool)

FILE DESCRIPTION & CODE STRUCTURE (in Visual Studio 2022):

📁 Project 3:
├──  Header Files: Header files for the game code
│   ├── Border.h: header file for the border, keeps color trails (from abilities) and players inside
│   ├── Explosion.h: header file for the explosion ability, quick animates it on screen when ability is activated
│   ├── GridManager.h: header file for the grid system, used to calculate points with steps taken by players
│   ├── Marker.h: header file for the color trail, appears behind player or when an ability is used
│   ├── Player.h: header file for the player (NOTE: this has been scrapped, a dud, we are not using this and instead using PlayerPointTracker instead)
│   ├── PlayerPointTracker.h: header file for the player, keeps tracks of player steps
│   ├── ScoreDisplay.h: header file for the score, converts steps to points
│   └── Timer.h: header file for the timer, ends game once timer reaches 0
│
├──  Resource Files: audio and sprite files for the game
│   ├── explosion.txt: explosion ability sprite
│   ├── marker1.txt: color trail for player 1 sprite
│   ├── marker2.txt: color trail for player 2 sprite
│   ├── player1.txt: player 1 sprite
│   ├── player1_wins.txt: player 1 winning sprite
│   ├── player2.txt: player 2 sprite
│   └── player2_wins.txt: player 2 winning sprite
│
└──  Source Files: C++ files for the game code
    ├── Border.cpp: C++ for the border, you can understand the rest
    ├── Explosion.cpp
    ├── game.cpp
    ├── GameOver.cpp
    ├── GameOver.h
    ├── GameStart.cpp
    ├── GameStart.h
    ├── GridManager.cpp
    ├── Marker.cpp
    ├── Player.cpp
    ├── PlayerPointTracker.cpp
    ├── ScoreDisplay.cpp
    └── Timer.cpp

libraries: Containing dragonfly library + SFML library

HOW TO COMPILE:
Extract the zip file, set environment path to PATH=%PATH%;$(solutiondir)libraries/SFML-3.0.0/bin in the properties tab under debugging Visual Studio 2022 (right click Project 3 to see the properties tab at the very bottom) and run the program in release mode

PLAYER 1 CONTROLS:
Use WASD to move
Use Q to shoot laser in the facing direction

PLAYER 2 CONTROLS:
Use UP, DOWN, LEFT, RIGHT to move
Use Right CTRL to place bomb around the player

TEAM: Avi - apal1@wpi.edu, Colin Masucci - cemasucci@wpi.edu
