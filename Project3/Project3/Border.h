#pragma once
#include "Object.h"
#include "Vector.h"

class Border : public df::Object {
private:
    int m_left, m_right, m_top, m_bottom;  // boundaries in game coordinates

public:
    Border(int left, int right, int top, int bottom);

    int draw() override;  // draws the border visually

    // Clamp a position to inside the border
    df::Vector clampToBorder(const df::Vector& pos) const;

    // Check if position is outside
    bool isOutside(const df::Vector& pos) const;

    int getLeft() const { return m_left; }
    int getRight() const { return m_right; }
    int getTop() const { return m_top; }
    int getBottom() const { return m_bottom; }
};