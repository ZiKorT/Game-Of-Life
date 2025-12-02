#include "../include/Grid.h"
#include "../include/FileManager.h"
#include <iostream>

Grid::Grid() : rows(0), cols(0) {
    rule = std::make_unique<Conway>();
}

bool Grid::loadFile(const std::string& filepath) {
    std::vector<std::vector<int>> gridData;

    //récupère les infos de l'input en utilisant FileManager.cpp
    if (!FileManager::readGridFile(filepath, rows, cols, gridData)) {
        return false;
    }

    //change la taille de la grille
    cells.resize(rows);
    for (int i = 0; i < rows; ++i) {
        cells[i].clear();
        cells[i].reserve(cols);

        for (int j = 0; j < cols; ++j) {
            bool alive = (gridData[i][j] == 1);
            cells[i].emplace_back(alive);
        }
    }
    return true;
}

int Grid::compteurVoisin(int x, int y) const {
    int count = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;

            // Gestion Torique
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
            int neighbors = compteurVoisin(i, j);
            std::unique_ptr<CellState> nextState = rule->apply(cells[i][j].getState(), neighbors);
            cells[i][j].prepareProchainEtat(std::move(nextState));
        }
    }
}

void Grid::update() {
    for (std::vector<Cell>& row : cells) {
        for (Cell& cell : row) {
            cell.majEtat();
        }
    }
}

const Cell& Grid::getCell(int x, int y) const {
    return cells[x][y];
}

bool Grid::operator==(const Grid& other) const { //permet de comparer 2 grilles
    if (rows != other.rows || cols != other.cols) return false;
    for(int i=0; i<rows; ++i) {
        for(int j=0; j<cols; ++j) {
            if (cells[i][j].estVivant() != other.cells[i][j].estVivant()) return false;
        }
    }
    return true;
}