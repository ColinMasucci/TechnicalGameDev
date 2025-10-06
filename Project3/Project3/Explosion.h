#pragma once
#include "Object.h"
#include "EventStep.h"

class Explosion : public df::Object {
private:
    int m_frame_count;      // total frames in the animation
    int m_current_frame;    // current frame
public:
    Explosion(const df::Vector& pos);

    int eventHandler(const df::Event* p_e) override;
    int draw() override; // optional if using standard sprite drawing
};
