#include "Explosion.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "ResourceManager.h"

Explosion::Explosion(const df::Vector& pos) {
    setType("Explosion");
    setPosition(pos);
    setSolidness(df::SPECTRAL);    // does not block movement

    // Load the sprite
    setSprite("explosion");
	setAltitude(3);          // on top of most everything
    m_current_frame = 0;
	m_frame_count = 8;

    // We want to receive step events
    registerInterest(df::STEP_EVENT);

}

int Explosion::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::STEP_EVENT) {
        m_current_frame = m_current_frame+1;
        // When we reach the last frame, remove ourselves
        if (m_current_frame >= m_frame_count) {
            WM.markForDelete(this);
        }
        return 1;
    }

    return 0;
}

//default
int Explosion::draw() {
    return df::Object::draw();
}
