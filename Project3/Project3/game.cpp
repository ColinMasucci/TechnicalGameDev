//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"

#include "Player.h"
#include "PlayerPointTracker.h"
#include "ScoreDisplay.h"
#include "Border.h"

void loadResources(void);
void populateWorld(void);

int main(int argc, char *argv[]) {

    // Start up Game Manager.
    if (GM.startUp()) {
        LM.writeLog("Error starting game manager!");
        GM.shutDown();
        return 1;
    }

    // Set flush of logfile during development (when done, make false).
    LM.setFlush(true);

    // Show splash screen.
    df::splash();

    // Load game resources.
    loadResources();

    // Populate game world with some objects.
    populateWorld();

    //Run Game
    GM.run();

    // Shut everything down.
    GM.shutDown();

    return 0;
}


void loadResources(void) {
    // Load sprites.
    RM.loadSprite("sprites/player1.txt", "player1");
    RM.loadSprite("sprites/player2.txt", "player2");
    RM.loadSprite("sprites/marker1.txt", "marker1");
    RM.loadSprite("sprites/marker2.txt", "marker2");
    RM.loadSprite("sprites/explosion.txt", "explosion");
    
    //Load Sounds
    //RM.loadSound("sounds/sounds/fire.wav", "fire");
}

void populateWorld(void) {
    // --- Create border first (draws behind everything else) ---
    int left = 1;
    int right = 70;     // adjust width as you prefer
    int top = 1;
    int bottom = 24;    // adjust height as you prefer
    Border* border = new Border(left, right, top, bottom);

    PlayerPointTracker* p1 = new PlayerPointTracker(1, df::Vector(5, 5));
    PlayerPointTracker* p2 = new PlayerPointTracker(2, df::Vector(50, 20));

    new ScoreDisplay(p1, p2);

    WM.insertObject(p1);
    WM.insertObject(p2);

	WM.insertObject(border);
}
