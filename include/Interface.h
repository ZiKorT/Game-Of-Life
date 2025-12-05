#pragma once
#define INTERFACE_HPP

#include "Grid.h"
#include <string>

class Interface {
public:
    virtual ~Interface() = default;
    virtual void run() = 0;
};

// Mode Console : Écriture fichier
class ConsoleInterface : public Interface {
private:
    Grid& grid;
    int iterations;
    std::string inputFilename;

public:
    ConsoleInterface(Grid& g, int iter, std::string filename);
    void run() override;
    void saveIteration(int iter); //sauvegarde l'etat de la grille dans un fichier
};

// Mode Graphique : SFML
class GraphicInterface : public Interface {
private:
    Grid& grid;
    int cellSize;
    int executionDelay; //permet de régler la vitesse d'exec du programme

public:
    GraphicInterface(Grid& g);
    void run() override;
};