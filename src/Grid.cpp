#include "../include/Grid.h"
#include "../include/FileManager.h"
#include <iostream>

Grid::Grid() : rows(0), cols(0) {
    // Par défaut, on utilise les règles classiques de Conway
    rule = std::make_unique<Conway>();
}

bool Grid::loadFile(const std::string& filepath) {
    std::vector<std::vector<int>> gridData;

    // 1. Lecture du fichier via le FileManager
    if (!FileManager::readGridFile(filepath, rows, cols, gridData)) {
        return false;
    }

    // 2. Initialisation de la grille
    cells.resize(rows);
    for (int i = 0; i < rows; ++i) {
        cells[i].clear();
        cells[i].reserve(cols);

        for (int j = 0; j < cols; ++j) {
            int val = gridData[i][j];

            // Création de base (Vivant si 1, Mort sinon)
            bool alive = (val == 1);
            Cell c(alive);

            // GESTION OBSTACLE : Si le fichier contient '2', c'est un mur
            if (val == 2) {
                c.devenirObstacle();
            }

            cells[i].push_back(std::move(c));
        }
    }
    return true;
}

int Grid::compteurVoisin(int x, int y) const {
    int count = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;

            // Logique Torique : Les bords sont connectés (effet Pac-Man)
            int nx = (x + dx + rows) % rows;
            int ny = (y + dy + cols) % cols;

            if (cells[nx][ny].estVivant()) {
                count++;
            }
        }
    }
    return count;
}

void Grid::parcoursGrille() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {

            // OPTIMISATION : Si c'est un obstacle, on ne calcule rien.
            // Il garde le même état (statique) pour le tour suivant.
            if (cells[i][j].estObstacle()) {
                cells[i][j].prepareProchainEtat(cells[i][j].getState().clone());
                continue;
            }

            // Calcul normal pour les cellules vivantes/mortes
            int neighbors = compteurVoisin(i, j);
            auto nextState = rule->apply(cells[i][j].getState(), neighbors);
            cells[i][j].prepareProchainEtat(std::move(nextState));
        }
    }
}

void Grid::update() {
    // On valide le nouvel état pour toutes les cellules
    for (auto& row : cells) {
        for (auto& cell : row) {
            cell.majEtat();
        }
    }
}

const Cell& Grid::getCell(int x, int y) const {
    return cells[x][y];
}

bool Grid::operator==(const Grid& other) const {
    if (rows != other.rows || cols != other.cols) return false;
    for(int i=0; i<rows; ++i) {
        for(int j=0; j<cols; ++j) {
            if (cells[i][j].estVivant() != other.cells[i][j].estVivant()) return false;
        }
    }
    return true;
}