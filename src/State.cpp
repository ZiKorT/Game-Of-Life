#include "../include/State.h"

//Vivante-
bool AliveState::estVivant() const { return true; }//Renvoie l'etat
char AliveState::symbole() const { return '1'; }//Renvoie le symbole
std::unique_ptr<CellState> AliveState::clone() const { return std::make_unique<AliveState>(); }

//Morte
bool DeadState::estVivant() const { return false; }
char DeadState::symbole() const { return '0'; }
std::unique_ptr<CellState> DeadState::clone() const { return std::make_unique<DeadState>(); }

//Obstacle
bool ObstacleState::estVivant() const { return false; }
char ObstacleState::symbole() const { return '2'; } // Symbole '2' pour les fichiers
std::unique_ptr<CellState> ObstacleState::clone() const { return std::make_unique<ObstacleState>(); }