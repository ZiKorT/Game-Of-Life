#include "../include/Interface.h"
#include "../include/FileManager.h"
#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>

namespace fs = std::filesystem;

//mode console

ConsoleInterface::ConsoleInterface(Grid& g, int iter, std::string filename)
    : grid(g), iterations(iter), inputFilename(filename) {}

void ConsoleInterface::run() {
    std::string folderName = inputFilename + "_out";
    if (!fs::exists(folderName)) {
        fs::create_directory(folderName);
    }

    for (int i = 0; i < iterations; ++i) {
        saveIteration(i);
        grid.parcoursGrille();
        grid.update();
    }
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
            int val = grid.getCell(i, j).estVivant() ? 1 : 0;
            dataToSave[i].push_back(val);
        }
    }

    //ECriture avec FileManager.cpp
    if (!FileManager::writeGridFile(path, rows, cols, dataToSave)) {
        std::cerr << "Erreur lors de la sauvegarde de " << path << std::endl;
    }
}

// --- GRAPHIC IMPLEMENTATION (SFML) ---

GraphicInterface::GraphicInterface(Grid& g)
    : grid(g), cellSize(20), executionDelay(100) {

    int savedDelay;
    // essaye de charger la vitesse depis le fichier de config
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
                if (grid.getCell(i, j).estVivant()) {
                    cellShape.setFillColor(sf::Color::White);
                } else {
                    cellShape.setFillColor(sf::Color(50, 50, 50));
                }
                cellShape.setPosition(j * cellSize, i * cellSize);
                window.draw(cellShape);
            }
        }
        window.display();
    }

    // Sauvegarde la vitesse dans config.txt avant de fermer
    FileManager::writeConfigInt("config.txt", executionDelay);
}