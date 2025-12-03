#include "../include/Cell.h"

Cell::Cell(bool startAlive) {
    if (startAlive) {
        etat = std::make_unique<AliveState>();
    } else {
        etat = std::make_unique<DeadState>();
    }
    prochainEtat = etat->clone();
}
Cell::Cell(const Cell& other) {
    etat = other.etat->clone();
    if (other.prochainEtat) {
        prochainEtat = other.prochainEtat->clone();
    } else {
        prochainEtat = nullptr;
    }
}


Cell& Cell::operator=(const Cell& other) {
    if (this != &other) {
        etat = other.etat->clone();
        if (other.prochainEtat) {
            prochainEtat = other.prochainEtat->clone();
        } else {
            prochainEtat = nullptr;
        }
    }
    return *this;
}
bool Cell::estVivant() const {
    return etat->estVivant();
}

char Cell::symbole() const {
    return etat->symbole();
}

void Cell::devenirObstacle() {
    etat = std::make_unique<ObstacleState>();
    prochainEtat = etat->clone();
}

bool Cell::estObstacle() const {
    return etat->estStatique();
}

void Cell::prepareProchainEtat(std::unique_ptr<CellState> newState) {
    prochainEtat = std::move(newState);
}
void Cell::majEtat() {
    if (prochainEtat) {
        etat = std::move(prochainEtat);
        prochainEtat = etat->clone();
    }
}

const CellState& Cell::getState() const {
    return *etat;
}
