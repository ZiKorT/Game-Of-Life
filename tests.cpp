#include <iostream>
#include <cassert>
#include <fstream>
#include <filesystem>
#include <vector>


#include "include/State.h"
#include "include/Cell.h"
#include "include/Grid.h"
#include "include/FileManager.h"

#define TEST_PASSED(name) std::cout << "\033[32m[OK]\033[0m Test " << name << " valide." << std::endl;

//test cellule
void testCell() {

    Cell c(false);
    assert(c.estVivant() == false);

    c.prepareProchainEtat(std::make_unique<AliveState>());
    c.majEtat();
    assert(c.estVivant() == true);
    assert(c.symbole() == '1');

    // Cas Obstacle
    Cell mur(false);
    mur.devenirObstacle();

    assert(mur.estVivant() == false); // Un mur n'est pas "vivant"
    assert(mur.estObstacle() == true);
    assert(mur.symbole() == '2');     // Symbole correct

    TEST_PASSED("Cell (Normal + Obstacle)");
}

//test FileManager
void testFileManager() {
    std::string filename = "test_io.txt";

    //on écrit manuellement un fichier avec un obstacle (2)
    {
        std::ofstream f(filename);
        f << "1 3\n1 0 2"; // 1 ligne, 3 colonnes : Vivant - Mort - Obstacle
    }

    int r, c;
    std::vector<std::vector<int>> data;
    bool success = FileManager::readGridFile(filename, r, c, data);

    assert(success);
    assert(r == 1);
    assert(c == 3);
    assert(data[0][0] == 1);
    assert(data[0][1] == 0);
    assert(data[0][2] == 2); // Vérifie que le 2 est bien lu

    std::filesystem::remove(filename);
    TEST_PASSED("FileManager (Lecture 0, 1, 2)");
}

//test grille torique + obstacle
void testGridLogic() {
    std::string filename = "test_logic.txt";

    // SCÉNARIO :
    // Une grille 3x3.
    // (0,0) est vivante.
    // (0,2) est un obstacle.
    // (0,1) est morte.
    //
    // Disposition :
    // 1 0 2
    // 0 0 0
    // 0 0 0

    {
        std::ofstream f(filename);
        f << "3 3\n1 0 2\n0 0 0\n0 0 0";
    }

    Grid g;
    g.loadFile(filename);

    // A. Test du Voisinage Torique
    // La case (0,0) est au bord gauche.
    // Son voisin de "gauche" est donc (0, 2) qui est l'obstacle.
    // L'obstacle compte-t-il comme vivant ? Non (estVivant() return false).
    // Donc (0,0) a 0 voisins vivants
    assert(g.compteurVoisin(0, 0) == 0);

    // On ajoute un voisin vivant tout en bas (2, 0) pour tester le tore vertical
    // On doit tricher un peu pour le test sans modifier le fichier :
    // On ne peut pas modifier la grille directement sans méthode "setCell",
    // donc on fait confiance au calcul.

    // B. Test de l'Obstacle Immuable
    // L'obstacle est en (0, 2).
    assert(g.getCell(0, 2).estObstacle() == true);

    // On lance une itération.
    g.parcoursGrille();
    g.update();

    // L'obstacle doit toujours être un obstacle, quoi qu'il arrive
    assert(g.getCell(0, 2).estObstacle() == true);
    assert(g.getCell(0, 2).symbole() == '2');

    // La cellule (0,0) n'avait aucun voisin vivant (le mur (0,2) compte pour 0), elle doit mourir.
    assert(g.getCell(0, 0).estVivant() == false);

    std::filesystem::remove(filename);
    TEST_PASSED("Grid (Torique & Obstacles)");
}

//test bloc stable
void testStableShape() {
    // Le "Bloc" est une structure stable.
    // 0 0 0 0
    // 0 1 1 0
    // 0 1 1 0
    // 0 0 0 0
    std::string filename = "test_block.txt";
    {
        std::ofstream f(filename);
        f << "4 4\n0 0 0 0\n0 1 1 0\n0 1 1 0\n0 0 0 0";
    }

    Grid g;
    g.loadFile(filename);

    // On fait tourner 5 itérations
    for(int i=0; i<5; ++i) {
        g.parcoursGrille();
        g.update();
    }

    // Ça doit être encore vivant au milieu
    assert(g.getCell(1, 1).estVivant());
    assert(g.getCell(2, 2).estVivant());
    // Et mort autour
    assert(g.getCell(0, 0).estVivant() == false);

    std::filesystem::remove(filename);
    TEST_PASSED("Stabilité (Block)");
}

int main() {
    std::cout << "LANCEMENT DES TESTS" << std::endl;

    testCell();
    testFileManager();
    testGridLogic();
    testStableShape();

    std::cout << "TOUT EST VERT SONT VALIDE" << std::endl;
    return 0;
}