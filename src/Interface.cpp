#include "../include/Interface.h"
#include "../include/FileManager.h"
#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>

namespace fs = std::filesystem;

// --- MODE CONSOLE ---

ConsoleInterface::ConsoleInterface(Grid& g, int iter, std::string filename)
    : grid(g), iterations(iter), inputFilename(filename) {}

void ConsoleInterface::run() {
    std::string folderName = inputFilename + "_out";
    if (!fs::exists(folderName)) {
        fs::create_directory(folderName);
    }

    for (int i = 0; i <= iterations; ++i) {

        std::cout << "=== ITERATION " << i << " / " << iterations << " ===" << std::endl;

        // 2. AFFICHAGE DANS LA CONSOLE
        for (int r = 0; r < grid.getRows(); ++r) {
            for (int c = 0; c < grid.getCols(); ++c) {
                char sym = grid.getCell(r, c).symbole();

                // On choisit un caractère joli pour l'affichage
                if (sym == '1') {
                    std::cout << "1 "; // Cellule Vivante
                } else if (sym == '2') {
                    std::cout << "X "; // Obstacle
                } else {
                    std::cout << ". "; // Cellule Morte
                }
            }
            std::cout << "\n"; // Fin de ligne
        }
        std::cout << std::endl;

        // 3. Sauvegarde et Calcul
        saveIteration(i);
        grid.parcoursGrille();
        grid.update();

        // Petit délai pour avoir le temps de voir (100ms)
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    // Sauvegarde finale
    saveIteration(iterations);
    std::cout << "Simulation terminee. Resultats dans " << folderName << std::endl;
}

void ConsoleInterface::saveIteration(int iter) {
    std::string path = inputFilename + "_out/iter_" + std::to_string(iter) + ".txt";

    std::vector<std::vector<int>> dataToSave;
    int rows = grid.getRows();
    int cols = grid.getCols();

    dataToSave.resize(rows);
    for (int i = 0; i < rows; ++i) {
        dataToSave[i].reserve(cols);
        for (int j = 0; j < cols; ++j) {
            // Conversion Cell en int
            char sym = grid.getCell(i, j).symbole();
            int val = 0;
            if (sym == '1') val = 1;
            if (sym == '2') val = 2;

            dataToSave[i].push_back(val);
        }
    }

    if (!FileManager::writeGridFile(path, rows, cols, dataToSave)) {
        std::cerr << "Erreur lors de la sauvegarde de " << path << std::endl;
    }
}

// --- MODE GRAPHIQUE (SFML) ---

GraphicInterface::GraphicInterface(Grid& g)
    : grid(g), cellSize(20), executionDelay(100) {

    int savedDelay;
    if (FileManager::readConfigInt("config.txt", savedDelay)) {
        executionDelay = savedDelay;
        std::cout << "Vitesse chargee depuis config.txt : " << executionDelay << "ms" << std::endl;
    }
}

void GraphicInterface::run() {
    int width = grid.getCols() * cellSize;
    int height = grid.getRows() * cellSize;

    sf::RenderWindow window(sf::VideoMode(width, height), "Jeu de la Vie - Projet POO");
    window.setFramerateLimit(60);

    bool paused = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) paused = !paused;

                if (event.key.code == sf::Keyboard::Up) {
                    executionDelay = std::max(0, executionDelay - 10);
                }
                if (event.key.code == sf::Keyboard::Down) {
                    executionDelay += 10;
                }

            }
        }

        if (!paused) {
            grid.parcoursGrille();
            grid.update();
            std::this_thread::sleep_for(std::chrono::milliseconds(executionDelay));
        }

        window.clear(sf::Color::Black);

        sf::RectangleShape cellShape(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));

        for (int i = 0; i < grid.getRows(); ++i) {
            for (int j = 0; j < grid.getCols(); ++j) {
                // GESTION COULEURS
                if (grid.getCell(i, j).estObstacle()) {
                    cellShape.setFillColor(sf::Color::Red);
                }
                else if (grid.getCell(i, j).estVivant()) {
                    cellShape.setFillColor(sf::Color::White);
                }
                else {
                    cellShape.setFillColor(sf::Color(50, 50, 50));
                }

                cellShape.setPosition(j * cellSize, i * cellSize);
                window.draw(cellShape);
            }
        }
        window.display();
    }

    FileManager::writeConfigInt("config.txt", executionDelay);
}