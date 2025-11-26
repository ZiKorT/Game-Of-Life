
#include "../include/Rule.h"

std::unique_ptr<CellState> ConwayRule::apply(const CellState& currentState, int aliveNeighbors) const {
    bool currentlyAlive = currentState.estVivant();

    if (currentlyAlive && (aliveNeighbors == 2 || aliveNeighbors == 3)) {
        return std::make_unique<AliveState>();
    }
    else if (!currentlyAlive && aliveNeighbors == 3) {
        return std::make_unique<AliveState>();
    }
    {
        return std::make_unique<DeadState>();
    }
}