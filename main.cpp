#include <iostream>
#include <string>
#include "include/Grid.h"
#include "include/Interface.h"

int main(int argc, char* argv[]) {
    // 1. Vérification des arguments
    // Le programme attend au moins : le nom du programme, le fichier, et le mode.
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <fichier_grille> <mode> [iterations]" << std::endl;
        std::cout << "Modes disponibles :" << std::endl;
        std::cout << "  0 = Mode Console (Génère des fichiers texte)" << std::endl;
        std::cout << "  1 = Mode Graphique (Interface SFML)" << std::endl;
        return 1;
    }

    // 2. Récupération des paramètres
    std::string filepath = argv[1];
    int mode = 0;

    try {
        mode = std::stoi(argv[2]);
    } catch (...) {
        std::cerr << "Erreur : Le mode doit etre un nombre entier (0 ou 1)." << std::endl;
        return 1;
    }

    Grid grid;
    if (!grid.loadFile(filepath)) {
        return 1;
    }

    if (mode == 0) {
        //mode console
        int iterations = 10;
        if (argc >= 4) {
            try {
                iterations = std::stoi(argv[3]);
            } catch (...) {
                std::cerr << "Attention : Nombre d'iterations invalide, utilisation de la valeur par defaut (10)." << std::endl;
            }
        }

        ConsoleInterface console(grid, iterations, filepath);
        console.run();
    }
    else if (mode == 1) {
        // --- MODE GRAPHIQUE ---
        GraphicInterface gui(grid);
        gui.run();
    }
    else {
        std::cerr << "Erreur : Mode inconnu '" << mode << "'. Utilisez 0 ou 1." << std::endl;
        return 1;
    }

    return 0;
}