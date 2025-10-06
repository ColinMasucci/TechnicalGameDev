#include "Marker.h"
#include "DisplayManager.h"

Marker::Marker(int owner, df::Vector pos) : m_owner(owner) {
    setType("Marker");
    setSolidness(df::SOFT);
    setPosition(pos);
    setAltitude(0);   // behind players
    if (m_owner == 1)
        setSprite("marker1");
    else
		setSprite("marker2");
}

//int Marker::draw() {
//    char c = (m_owner == 1 ? 'x' : 'o');
//    df::Color col = (m_owner == 1 ? df::YELLOW : df::CYAN);
//    DM.drawCh(getPosition(), c, col);
//    return 0;
//}
