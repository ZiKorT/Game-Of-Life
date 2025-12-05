//
// Created by ZiKor on 26/11/2025.
//

#pragma once
#define RULE_HPP

#include "State.h"

class GameRule {
public:
    virtual ~GameRule() = default;
    virtual std::unique_ptr<CellState> apply(const CellState& currentState, int aliveNeighbors) const = 0;
};

class Conway : public GameRule {
public:
    //Renvoie le prochain état d'une ccellule
    std::unique_ptr<CellState> apply(const CellState& currentState, int aliveNeighbors) const override;
};