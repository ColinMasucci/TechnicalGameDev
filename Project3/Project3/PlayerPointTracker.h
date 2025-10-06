#pragma once
#include "Object.h"
#include "Vector.h"
#include "EventKeyboard.h"

class PlayerPointTracker : public df::Object {
private:
    int m_player_id;                // 1 or 2
    df::Vector m_target_pos;        // current target grid cell
    df::Vector m_target_dir;        // current target grid cell direction
    bool m_moving;                  // true if moving toward target
    int m_score;                    // how many cells are claimed
    bool m_pressing_move;

    float m_cooldown = 5.0f;         // seconds
    float m_time_since_last = 0.0f;  // seconds
    bool  m_ability_active = false;


public:
    PlayerPointTracker(int id, df::Vector start_pos);

    int eventHandler(const df::Event* p_e) override;
    int draw() override;
    int getId() const { return m_player_id; } // to check for player ID

    void update();                  // called every step
    int getScore() const { return m_score; }
    void incrementScore() { m_score++; }
    void decrementScore() { m_score--; }


    void useLaser();
    void useBomb();

private:
    void startMove(const df::Vector& dir);
    void leaveMarker(const df::Vector& cell);
};
