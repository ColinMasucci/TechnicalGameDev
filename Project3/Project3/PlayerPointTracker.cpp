#include "PlayerPointTracker.h"
#include "Marker.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "EventKeyboard.h"
#include "DisplayManager.h"
#include "GridManager.h"
#include "ObjectList.h"
#include "Explosion.h"

#include <iostream>



PlayerPointTracker::PlayerPointTracker(int id, df::Vector start_pos)
    : m_player_id(id), m_target_pos(start_pos), m_moving(false), m_score(0) {

    setType("PlayerPointTracker");
    setSolidness(df::HARD);
    setPosition(start_pos);
    setAltitude(1);

    // register for events
    registerInterest(df::STEP_EVENT);
    registerInterest(df::KEYBOARD_EVENT);

	m_pressing_move = false;
}

int PlayerPointTracker::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::STEP_EVENT) {
        update();
        return 1;
    }

    if (p_e->getType() == df::KEYBOARD_EVENT) {
        const auto* p_k = dynamic_cast<const df::EventKeyboard*>(p_e);

		if (!p_k) return 0;

        if (p_k->getKeyboardAction() == df::KEY_RELEASED) {

            if (m_player_id == 1) {
                // WASD
                if (p_k->getKey() == df::Keyboard::W || p_k->getKey() == df::Keyboard::S || p_k->getKey() == df::Keyboard::A || p_k->getKey() == df::Keyboard::D) m_pressing_move = false;
            }
            else {
                // Arrow keys
                if (p_k->getKey() == df::Keyboard::UPARROW || p_k->getKey() == df::Keyboard::DOWNARROW || p_k->getKey() == df::Keyboard::LEFTARROW || p_k->getKey() == df::Keyboard::RIGHTARROW) m_pressing_move = false;
            }
        }

        if (p_k->getKeyboardAction() == df::KEY_DOWN) {
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

            if (dir.getMagnitude() > 0) {      // picked a direction
                m_pressing_move = true;
                m_target_dir = dir;
				if (!m_moving) startMove(dir);
            }
        }

        // Ability activation
        if (p_k->getKeyboardAction() == df::KEY_PRESSED) {
            if (m_time_since_last >= m_cooldown) {
                if (m_player_id == 1 && p_k->getKey() == df::Keyboard::Q) {
                    useLaser();
                    m_time_since_last = 0.0f;
                }
                else if (m_player_id == 2 && p_k->getKey() == df::Keyboard::RIGHTCONTROL) {
                    useBomb();
                    m_time_since_last = 0.0f;
                }
            }
        }

        return 1;
    }
    return 0;
}

void PlayerPointTracker::startMove(const df::Vector& dir) {
    // leave marker behind
    leaveMarker(getPosition());

    // set next target cell
    m_target_pos = getPosition() + dir;
    m_moving = true;
}

void PlayerPointTracker::update() {
    // accumulate time since last ability
    m_time_since_last += 1.0f / 30.0f;

    if (!m_moving && !m_pressing_move) return;

    // move gradually toward target
    df::Vector pos = getPosition();
    df::Vector diff = m_target_pos - pos;

    // step by 0.2 per frame (tweak for speed)
    float step = 0.2f;
    if (fabs(diff.getX()) > step) pos.setX(pos.getX() + step * (diff.getX() > 0 ? 1 : -1));
    else                          pos.setX(m_target_pos.getX());

    if (fabs(diff.getY()) > step) pos.setY(pos.getY() + step * (diff.getY() > 0 ? 1 : -1));
    else                          pos.setY(m_target_pos.getY());

    setPosition(pos);

    // reached grid cell
    if (pos == m_target_pos) {
        m_moving = false;
        if (m_pressing_move) {
            startMove(m_target_dir); // continue if still pressing
        }
    }
        
}

void PlayerPointTracker::leaveMarker(const df::Vector& cell) {
    int x = static_cast<int>(cell.getX());
    int y = static_cast<int>(cell.getY());

    GridManager& grid = GridManager::getInstance();
    int prev_owner = grid.getOwner(x, y);

    // Update scores if cell is being repainted
    if (prev_owner != m_player_id) {
        if (prev_owner != 0) {
            // find previous owner and decrement their score
            df::ObjectList objs = WM.objectsOfType("PlayerPointTracker");
            for (df::ObjectListIterator it(&objs); !it.isDone(); it.next()) {
                auto* player = dynamic_cast<PlayerPointTracker*>(it.currentObject());
                if (player && player->getId() == prev_owner)
                    player->decrementScore();
            }
        }

        // Increment this player's score
        incrementScore();
        grid.claimCell(x, y, m_player_id);
    }

    // Create or recolor the marker visually
    Marker* m = new Marker(m_player_id, cell);
    WM.insertObject(m);
}

int PlayerPointTracker::draw() {
    // simple colored square
    char c = (m_player_id == 1 ? '1' : '2');
    df::Color color = (m_player_id == 1 ? df::YELLOW : df::CYAN);
    DM.drawCh(getPosition(), c, color);
    return 0;
}



void PlayerPointTracker::useLaser() {
    df::Vector pos = getPosition();
    df::Vector dir = m_target_dir;
    if (dir.getMagnitude() == 0)    // if not moving, pick default up
        dir = df::Vector(0, -1);

    GridManager& grid = GridManager::getInstance();

    // maximum distance e.g. 10 cells
    for (int i = 1; i <= 10; ++i) {
		df::Vector newDir = df::Vector(dir.getX() * i, dir.getY() * i);
        df::Vector cell = pos + newDir;

        // claim this cell
        leaveMarker(cell);

        // for animation, create a special marker (red beam)
        Marker* beam = new Marker(m_player_id, cell);
        //beam->setTemporary(true);         // we’ll remove it after some frames
        //WM.insertObject(beam);
    }
}

void PlayerPointTracker::useBomb() {
    df::Vector center = getPosition();
    GridManager& grid = GridManager::getInstance();

    // 4x4 area centered on player
    int radius = 2;
    for (int dx = -radius; dx <= radius; ++dx) {
        for (int dy = -radius; dy <= radius; ++dy) {
            df::Vector cell = center + df::Vector(dx, dy);
            leaveMarker(cell);
        }
    }
    // spawn explosion
    df::Vector pos = getPosition();
    Explosion* explosion = new Explosion(pos);
    WM.insertObject(explosion);
}
