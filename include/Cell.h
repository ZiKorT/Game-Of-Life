#ifndef CELL_H
#define CELL_H

#include "State.h"
#include <memory>

class Cell {
private:
    std::unique_ptr<CellState> etat;//etat de la cellule
    std::unique_ptr<CellState> prochainEtat;//etat suivant

public:
    Cell(bool startAlive = false);//pour dire qu'une cellule est morte de base

    Cell(const Cell& other);//constructeur de copie
    Cell& operator=(const Cell& other);//operateur de copie

    bool estVivant() const;
    char symbole() const;

    void devenirObstacle();

    bool estObstacle() const;

    void prepareProchainEtat(std::unique_ptr<CellState> newState);
    void majEtat();
    const CellState& getState() const;
};

#endif