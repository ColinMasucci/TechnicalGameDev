//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"

#include "Player.h"

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
    RM.loadSprite("sprites/player.txt", "player");
    
    //Load Sounds
    //RM.loadSound("sounds/sounds/fire.wav", "fire");
}

void populateWorld(void) {
    Player* p1 = new Player(1, df::Vector(5, 5));
    Player* p2 = new Player(2, df::Vector(30, 20));

    WM.insertObject(p1);
    WM.insertObject(p2);
}