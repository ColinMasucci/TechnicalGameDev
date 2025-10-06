#include "ScoreDisplay.h"
#include "DisplayManager.h"

ScoreDisplay::ScoreDisplay(PlayerPointTracker* p1, PlayerPointTracker* p2)
    : m_p1(p1), m_p2(p2) {
    setType("ScoreDisplay");
    setSolidness(df::SPECTRAL);
    setAltitude(10);
    registerInterest(df::STEP_EVENT);
}

int ScoreDisplay::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::STEP_EVENT)
        return 1;
    return 0;
}

int ScoreDisplay::draw() {
    if (!m_p1 || !m_p2) return 0;

    std::string text = "P1: " + std::to_string(m_p1->getScore()) +
        "   P2: " + std::to_string(m_p2->getScore());
    df::Vector pos(5, 1); // near top-left
    DM.drawString(pos, text, df::LEFT_JUSTIFIED, df::WHITE);

    return 0;
}
