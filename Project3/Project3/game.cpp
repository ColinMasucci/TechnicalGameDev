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
    
    //Load Sounds
    //RM.loadSound("sounds/sounds/fire.wav", "fire");
}

void populateWorld(void) {
    // Note: Constant speed not updated yet for PlayerPointTracker, but able to implement point system
    //Player* p1 = new Player(1, df::Vector(5, 5));
    //Player* p2 = new Player(2, df::Vector(50, 20));

    PlayerPointTracker* p1 = new PlayerPointTracker(1, df::Vector(5, 5));
    PlayerPointTracker* p2 = new PlayerPointTracker(2, df::Vector(50, 20));

    new ScoreDisplay(p1, p2);

    WM.insertObject(p1);
    WM.insertObject(p2);
}
