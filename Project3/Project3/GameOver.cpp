#include "EventStep.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "GameOver.h"
#include "GameStart.h"
#include "DisplayManager.h"

GameOver::GameOver(int winner) {

    setType("GameOver");

    if (winner == 1) {
        setSprite("player1_wins");
    }
    else if (winner == 2) {
        setSprite("player2_wins");
    }
    else {
		setSprite("losers");
    }

    // Put in center of window.
    //setLocation(df::CENTER_CENTER);
	df::Vector win_pos = df::Vector((float)(DM.getHorizontal() / 2), (float)(DM.getVertical() / 2));
    setPosition(win_pos);


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
