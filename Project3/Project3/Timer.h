#pragma once
#include "Object.h"
#include "EventStep.h"
#include "PlayerPointTracker.h"

class Timer : public df::Object {
private:
    int m_steps_remaining; // steps left before timer ends
    bool m_time_up;        // whether time is finished

public:
    Timer(int seconds);    // seconds to count down

    int eventHandler(const df::Event* p_e) override;
    int draw() override;

    bool isTimeUp() const { return m_time_up; }
};