#include "../include/FileManager.h"
#include <fstream>
#include <iostream>

// Lecture de la grille
bool FileManager::readGridFile(const std::string& filepath, int& rows, int& cols, std::vector<std::vector<int>>& gridData) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filepath << std::endl;
        return false;
    }

    if (!(file >> rows >> cols)) {
        std::cerr << "Erreur : Format de fichier invalide" << std::endl;
        return false;
    }
    gridData.resize(rows);
    for (int i = 0; i < rows; ++i) {
        gridData[i].reserve(cols);
        for (int j = 0; j < cols; ++j) {
            int val;
            file >> val;
            gridData[i].push_back(val);
        }
    }

    file.close();
    return true;
}

// Écriture de la grille
bool FileManager::writeGridFile(const std::string& filepath, int rows, int cols, const std::vector<std::vector<int>>& gridData) {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible d'écrire dans " << filepath << std::endl;
        return false;
    }

    file << rows << " " << cols << "\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file << gridData[i][j] << (j == cols - 1 ? "" : " ");
        }
        file << "\n";
    }

    file.close();
    return true;
}

// Lecture Config
bool FileManager::readConfigInt(const std::string& filepath, int& value) {
    std::ifstream file(filepath);
    if (file.is_open()) {
        file >> value;
        return true;
    }
    return false;
}

//Ecriture Config$
bool FileManager::writeConfigInt(const std::string& filepath, int value) {
    std::ofstream file(filepath);
    if (file.is_open()) {
        file << value;
        return true;
    }
    return false;
}