#pragma once
#include "Object.h"
#include "EventStep.h"
#include "PlayerPointTracker.h"

class ScoreDisplay : public df::Object {
private:
    PlayerPointTracker* m_p1;
    PlayerPointTracker* m_p2;

public:
    ScoreDisplay(PlayerPointTracker* p1, PlayerPointTracker* p2);
    int eventHandler(const df::Event* p_e) override;
    int draw() override;
};

