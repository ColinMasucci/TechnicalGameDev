#include "GridManager.h"

GridManager& GridManager::getInstance() {
    static GridManager instance;
    return instance;
}

void GridManager::claimCell(int x, int y, int player_id) {
    ownership[{x, y}] = player_id;
}

int GridManager::getOwner(int x, int y) const {
    auto it = ownership.find({ x, y });
    if (it != ownership.end())
        return it->second;
    return 0;
}
