#include "Timer.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "ObjectList.h"
#include "EventStep.h"
#include "PlayerPointTracker.h"


Timer::Timer(int seconds) {
    setType("Timer");
    registerInterest(df::STEP_EVENT);

    // convert seconds to steps
    m_steps_remaining = seconds * 30;
    m_time_up = false;

    setSolidness(df::SPECTRAL);
    setAltitude(10); // draw above most elements
}

int Timer::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::STEP_EVENT && !m_time_up) {
        m_steps_remaining--;

        if (m_steps_remaining <= 0) {
            m_steps_remaining = 0;
            m_time_up = true;

            // Pause players
            PlayerPointTracker* p1 = nullptr;
            PlayerPointTracker* p2 = nullptr;

            df::ObjectList players = WM.objectsOfType("PlayerPointTracker");
            for (df::ObjectListIterator it(&players); !it.isDone(); it.next()) {
                auto* player = dynamic_cast<PlayerPointTracker*>(it.currentObject());
                if (!player) continue;
                if (player->getId() == 1) p1 = player;
                if (player->getId() == 2) p2 = player;
                player->setActive(false); // freeze movement
            }

            // display the winner
            if (p1 && p2) {
                // new WinnerDisplay(p1, p2);
            }
        }
        return 1;
    }
    return 0;
}

int Timer::draw() {
    int seconds_left = m_steps_remaining / 30;

    df::Vector pos(35, 0); 
    if (!m_time_up) {
        std::string time_text = "Time Left: " + std::to_string(seconds_left) + "s";
        DM.drawString(pos, time_text, df::CENTER_JUSTIFIED, df::WHITE);
    }
    else {
        std::string end_text = "TIME'S UP!";
        DM.drawString(pos, end_text, df::CENTER_JUSTIFIED, df::RED);
    }
    return 0;
}
