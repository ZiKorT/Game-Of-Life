#pragma once
#define GRID_H

#include <vector>
#include <string>
#include <memory>
#include "Cell.h"
#include "Rule.h"

class Grid {
private:
    int rows;
    int cols;
    std::vector<std::vector<Cell>> cells;
    std::unique_ptr<GameRule> rule;

public:
    Grid();

    bool loadFile(const std::string& filepath);//charge le fichier

    int compteurVoisin(int x, int y) const;//compte le nb de voisin
    void parcoursGrille();//parcours la grille
    void update();//met à jour toutes les cellules

    //getter
    int getRows() const { return rows; }
    int getCols() const { return cols; }
    const Cell& getCell(int x, int y) const;

    //pour les tests
    bool operator==(const Grid& other) const;
};