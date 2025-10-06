#pragma once
#include "Object.h"
#include "Vector.h"

class Marker : public df::Object {
private:
    int m_owner; // which player owns this cell
public:
    Marker(int owner, df::Vector pos);
    int getOwner() const { return m_owner; }

    //int draw() override;
};
