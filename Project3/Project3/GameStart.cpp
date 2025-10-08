#include "Color.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "GameStart.h"

#include "Music.h"

GameStart::GameStart() {
    setType("GameStart");

    // Link to "message" sprite.
    setSprite("gamestart");

    // Put in center of screen.
    setLocation(df::CENTER_CENTER);

    // Register for "keyboard" event.
    registerInterest(df::KEYBOARD_EVENT);

    // Play start music.
    p_music = RM.getMusic("theme");
    playMusic();
}

// Handle event.
// Return 0 if ignored, else 1.
int GameStart::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::KEYBOARD_EVENT) {
        df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*)p_e;
        switch (p_keyboard_event->getKey()) {
        case df::Keyboard::P: 			// play
            start();
            break;
        default:
            break;
        }
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}

void GameStart::start() {

    
}

// Override default draw so as not to display "value".
int GameStart::draw() {
    return df::Object::draw();
}

//play start music
void GameStart::playMusic() {
    if (p_music)
        p_music->play();
}

//play start music
void GameStart::pauseMusic() {
    if (p_music)
        p_music->pause();
}