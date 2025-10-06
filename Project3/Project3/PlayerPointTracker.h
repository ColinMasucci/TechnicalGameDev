#pragma once
#include "Object.h"
#include "Vector.h"
#include "EventKeyboard.h"

class PlayerPointTracker : public df::Object {
private:
    int m_player_id;                // 1 or 2
    df::Vector m_target_pos;        // current target grid cell
    bool m_moving;                  // true if moving toward target
    int m_score;                    // how many cells are claimed

public:
    PlayerPointTracker(int id, df::Vector start_pos);

    int eventHandler(const df::Event* p_e) override;
    int draw() override;
    int getId() const { return m_player_id; } // to check for player ID

    void update();                  // called every step
    int getScore() const { return m_score; }
    void incrementScore() { m_score++; }
    void decrementScore() { m_score--; }

private:
    void startMove(const df::Vector& dir);
    void leaveMarker(const df::Vector& cell);
};
