//New Player script that is closer to TRON

#include "Player.h"
#include "Vector.h"
#include "Color.h"
#include "Object.h"
#include "Marker.h"
#include "Particle.h"

#include "EventStep.h"
#include "EventKeyboard.h"
#include "EventCollision.h"

#include "WorldManager.h"
#include "DisplayManager.h"



Player::Player(int id, df::Vector start_pos)
    : m_player_id(id), m_alive(true){

    setType("Player");
    setSprite("player");
    setSolidness(df::HARD);
    setPosition(start_pos);
    setAltitude(1);
    // register for events
    registerInterest(df::STEP_EVENT);
	registerInterest(df::KEYBOARD_EVENT);


	//initialize direction and target position
    if (m_player_id == 1) {
        m_target_dir = df::Vector(1, 0);  // start moving right
    }
    else {
        m_target_dir = df::Vector(-1, 0); // start moving left
	}
	updateTarget();
}

int Player::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::STEP_EVENT) {
        update();
        return 1;
    }

    if (p_e->getType() == df::KEYBOARD_EVENT) {
		return handleInput(p_e);
    }

    if (p_e->getType() == df::COLLISION_EVENT) {
        return handleCollision(static_cast<const df::EventCollision*>(p_e));
    }
    return 0;
}

int Player::handleInput(const df::Event* p_e) {
    const auto* p_k = dynamic_cast<const df::EventKeyboard*>(p_e);
    if (!p_k)      
        return 0;

    if (p_k->getKeyboardAction() == df::KEY_PRESSED) {
        df::Vector dir(0, 0);
        if (m_player_id == 1) {
            // WASD
            if (p_k->getKey() == df::Keyboard::W) dir = df::Vector(0, -1);
            else if (p_k->getKey() == df::Keyboard::S) dir = df::Vector(0, 1);
            else if (p_k->getKey() == df::Keyboard::A) dir = df::Vector(-1, 0);
            else if (p_k->getKey() == df::Keyboard::D) dir = df::Vector(1, 0);
        }
        else {
            // Arrow keys
            if (p_k->getKey() == df::Keyboard::UPARROW) dir = df::Vector(0, -1);
            else if (p_k->getKey() == df::Keyboard::DOWNARROW) dir = df::Vector(0, 1);
            else if (p_k->getKey() == df::Keyboard::LEFTARROW) dir = df::Vector(-1, 0);
            else if (p_k->getKey() == df::Keyboard::RIGHTARROW) dir = df::Vector(1, 0);
        }

        // Ignore zero vector
        if (dir != df::Vector(0, 0)) {

            // Check we are not reversing direction (no 180° turns)
            bool reversing_x = (dir.getX() > 0 && m_target_dir.getX() > 0) ||
                (dir.getX() < 0 && m_target_dir.getX() < 0);
            bool reversing_y = (dir.getY() > 0 && m_target_dir.getY() > 0) ||
                (dir.getY() < 0 && m_target_dir.getY() < 0);

            // If the new direction is not opposite of current (so 90° turn is allowed)
            if (!(reversing_x || reversing_y)) {

                // Scale Y movement to match X speed
                if (dir.getY() != 0)
                    dir.setY(0.7f * dir.getY());

                m_target_dir = dir;
            }
        }
    }
    return 1;
}

void Player::update() {
    if (!m_alive) return;

	// check if reached target cell/close enough
    if (getPosition().getX()-m_target_pos.getX() < 0.1 && getPosition().getY() - m_target_pos.getY() < 0.1) {
		setPosition(m_target_pos);  // snap to target position
        leaveMarker();
        updateTarget();
	}
	df::Vector newDir = multiplyVector(m_target_dir, PLAYER_SPEED); // scale direction by speed

	setVelocity(newDir);  // set velocity to current target direction     
    
}

int Player::handleCollision(const df::EventCollision* p_c) {
    // Identify the other object
    df::Object* p_obj1 = p_c->getObject1();
    df::Object* p_obj2 = p_c->getObject2();


    // If colliding with another player
    if (p_obj1->getType() == "Player" || p_obj2->getType() == "Player") {
        die();                           // Current player dies
        return 1;                         // Event handled
    }

    // If colliding with a trail marker
    if (p_obj1->getType() == "Marker" || p_obj2->getType() == "Marker") {
        die();                           // Hit a wall, die
        return 1;
    }

    return 0; // Not handled
}



//int Player::draw() {
//    // simple colored square
//    char c = (m_player_id == 1 ? '1' : '2');
//    df::Color color = (m_player_id == 1 ? df::YELLOW : df::CYAN);
//    DM.drawCh(getPosition(), c, color);
//
//    return 0;
//}

void Player::updateTarget() {
	m_target_pos = getPosition() + m_target_dir;
	m_prev_pos = getPosition();
}

df::Vector Player::multiplyVector(const df::Vector& v, float scalar) {
    df::Vector result = df::Vector(v.getX() * scalar, v.getY() * scalar);
	return result;
}

void Player::leaveMarker() {
    // Create a marker at the cell we just left
    Marker* m = new Marker(m_player_id, m_prev_pos);
    WM.insertObject(m);
}


void Player::die() {
    m_alive = false;
    setVelocity(df::Vector(0, 0)); // stop moving
    setSolidness(df::SPECTRAL);     // become non-collidable
	spawnParticle(getPosition());
}

void Player::spawnParticle(const df::Vector& pos) {
    // create a particle (size, lifetime, opacity, color)
    df::Particle* p = new df::Particle(
        0.3f,              // size (cell units)
        30,                // age (lifetime in steps)
        255,               // opacity (0-255)
        df::YELLOW         // color (can also use r,g,b)
    );

    p->setPosition(pos);   // put particle where you want
    WM.insertObject(p);    // register with the world
}