#include "EventStep.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "GameOver.h"
#include "GameStart.h"

GameOver::GameOver() {

    setType("GameOver");

	setSprite("player1_wins");

    // Put in center of window.
    setLocation(df::CENTER_CENTER);

    // Register for step event.
    registerInterest(df::STEP_EVENT);

    df::ObjectList object_list = WM.getAllObjects(true);
    for (int i = 0; i < object_list.getCount(); i++) {
        df::Object* p_o = object_list[i];
        if (p_o->getType() == "GameStart") {
            dynamic_cast <GameStart*>(p_o)->pauseMusic(); // Resume start music.
        }
    }

    // Play "game over" sound.
    df::Sound* p_sound = RM.getSound("gameover");
    if (p_sound)
        p_sound->play();

}

// When done, game over so reset things for GameStart.
GameOver::~GameOver() {

    
}

// Handle event.
// Return 0 if ignored, else 1.
int GameOver::eventHandler(const df::Event* p_e) {

    // If get here, have ignored this event.
    return 0;
}


// Override default draw so as not to display "value".
int GameOver::draw() {
    return df::Object::draw();
}
