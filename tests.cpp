#include <iostream>
#include <cassert>
#include <fstream>
#include <filesystem>

#include "include/State.h"
#include "include/Cell.h"
#include "include/Grid.h"
#include "include/FileManager.h"

#define TEST_PASSED(name) std::cout << "[OK] Test " << name << " passe." << std::endl;

//Test State.cpp
void testState() {
    AliveState vivant;
    DeadState mort;

    assert(vivant.estVivant() == true);
    assert(vivant.symbole() == '1');

    assert(mort.estVivant() == false);
    assert(mort.symbole() == '0');

    // Test du clone (Copie profonde)
    std::unique_ptr<CellState> copie = vivant.clone();
    assert(copie->estVivant() == true);
    assert(copie.get() != &vivant); // Vérifie que les adresses mémoire sont différentes

    TEST_PASSED("State");
}

//Test Cell.cpp
void testCell() {
    //Création
    Cell c(false); // Morte par défaut
    assert(c.estVivant() == false);

    //Préparation futur
    c.prepareProchainEtat(std::make_unique<AliveState>());
    //L'état actuel ne doit pas changer tout de suite
    assert(c.estVivant() == false);

    //MAJ
    c.majEtat();
    // Maintenant ça doit changer
    assert(c.estVivant() == true);

    //Copie de cellule
    Cell c2 = c;
    assert(c2.estVivant() == true);

    TEST_PASSED("Cell");
}

//Test FileManager
void testFileManager() {
    std::string filename = "test_temp.txt";

    //Création d'un fichier grille fictif
    {
        std::ofstream file(filename);
        file << "3 3\n0 1 0\n0 0 0\n1 1 1";
    }

    //Lecture
    int r, c;
    std::vector<std::vector<int>> data;
    bool success = FileManager::readGridFile(filename, r, c, data);

    assert(success == true);
    assert(r == 3);
    assert(c == 3);
    assert(data[0][1] == 1); // La case vivante ligne 0
    assert(data[2][0] == 1); // La case vivante ligne 2

    //ecriture config
    FileManager::writeConfigInt("config_test.txt", 500);
    int val;
    FileManager::readConfigInt("config_test.txt", val);
    assert(val == 500);

    //nettoyage
    std::filesystem::remove(filename);
    std::filesystem::remove("config_test.txt");

    TEST_PASSED("FileManager");
}

//Test Grid.cpp
void testGrid() {
    // On va tester le "Bloc" (Still life) : un carré de 2x2 ne doit jamais bouger.
    // 0 0 0 0
    // 0 1 1 0
    // 0 1 1 0
    // 0 0 0 0

    std::string filename = "test_block.txt";
    {
        std::ofstream file(filename);
        file << "4 4\n0 0 0 0\n0 1 1 0\n0 1 1 0\n0 0 0 0";
    }

    Grid g;
    g.loadFile(filename);

    //verif initiale
    assert(g.getCell(1, 1).estVivant());
    assert(g.compteurVoisin(1, 1) == 3); // Doit avoir 3 voisins (1,2), (2,1), (2,2)

    //on lance une itération
    g.parcoursGrille();
    g.update();

    //rien ne doit avoir changé (c'est un bloc stable)
    assert(g.getCell(1, 1).estVivant());
    assert(g.getCell(0, 0).estVivant() == false);

    //test torique
    // On met une cellule seule en (0,0).
    // Son voisin de gauche est en (0, cols-1).
    std::string fileTorique = "test_torique.txt";
    {
        std::ofstream f(fileTorique);
        f << "3 3\n1 0 0\n0 0 0\n0 0 0"; // Juste un 1 en haut à gauche
    }
    g.loadFile(fileTorique);
    // La case (0, 2) est à l'extrême droite. Son voisin de droite est (0, 0)
    // Donc (0, 2) doit voir 1 voisin vivant.
    assert(g.compteurVoisin(0, 2) == 1);

    std::filesystem::remove(filename);
    std::filesystem::remove(fileTorique);

    TEST_PASSED("Grid & Logique Torique");
}

int main() {
    std::cout << "LANCEMENT DES TESTS UNITAIRES" << std::endl;

    testState();
    testCell();
    testFileManager();
    testGrid();

    std::cout << "TOUS LES TESTS SONT VALIDES" << std::endl;
    return 0;
}
