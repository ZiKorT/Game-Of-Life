#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>

class FileManager {
public:
    // lit le fichier d'entrée
    static bool readGridFile(const std::string& filepath, int& rows, int& cols, std::vector<std::vector<int>>& gridData);

    // écrit l'état actuel pour le mode console
    static bool writeGridFile(const std::string& filepath, int rows, int cols, const std::vector<std::vector<int>>& gridData);

    // LIt le fichier config
    static bool readConfigInt(const std::string& filepath, int& value);

    // Ecrit une valeur dans le fichier config
    static bool writeConfigInt(const std::string& filepath, int value);
};

#endif