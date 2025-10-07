#include "Border.h"
#include "DisplayManager.h"

Border::Border(int left, int right, int top, int bottom)
    : m_left(left), m_right(right), m_top(top), m_bottom(bottom) {
    setType("Border");
    setSolidness(df::SPECTRAL);   // not collidable
    setAltitude(0);
}

int Border::draw() {
    for (int x = m_left; x <= m_right; x++) {
        DM.drawCh(df::Vector(x, m_top), '-', df::YELLOW);
        DM.drawCh(df::Vector(x, m_bottom), '-', df::YELLOW);
    }
    for (int y = m_top + 1; y < m_bottom; y++) {
        DM.drawCh(df::Vector(m_left, y), '|', df::YELLOW);
        DM.drawCh(df::Vector(m_right, y), '|', df::YELLOW);
    }
    return 0;
}


bool Border::isOutside(const df::Vector& pos) const {
    return (pos.getX() <= m_left || pos.getX() >= m_right ||
        pos.getY() <= m_top || pos.getY() >= m_bottom);
}

df::Vector Border::clampToBorder(const df::Vector& pos) const {
    df::Vector clamped = pos;
    if (pos.getX() < m_left + 1) clamped.setX(m_left + 1);
    if (pos.getX() > m_right - 1) clamped.setX(m_right - 1);
    if (pos.getY() < m_top + 1) clamped.setY(m_top + 1);
    if (pos.getY() > m_bottom - 1) clamped.setY(m_bottom - 1);
    return clamped;
}