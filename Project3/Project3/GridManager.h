#pragma once
#include <map>
#include "Vector.h"

class GridManager {
private:
    // (x,y) grid cell -> player_id (0 = unclaimed)
    std::map<std::pair<int, int>, int> ownership;

    GridManager() = default;

public:
    static GridManager& getInstance();

    // Record ownership of cell (x,y) by player_id
    void claimCell(int x, int y, int player_id);

    // Return current owner of (x,y)
    int getOwner(int x, int y) const;
};
