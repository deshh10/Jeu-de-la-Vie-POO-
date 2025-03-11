#include "FileManager.hpp"
#include <SFML/Graphics.hpp>

// Chargement d'une grille à partir d'un fichier
std::vector<std::vector<bool>> FileManager::loadFromFile(const std::string& filename, int& width, int& height) {
    std::ifstream file(filename); // Ouvrir le fichier en mode lecture
    if (file.is_open()) {
        // Lecture des dimensions de la grille
        file >> height >> width; //lit deux entiers depuis le fichier et les stocke dans les variables height et width. Ces valeurs représentent les dimensions de la grille.

        if (width <= 0 || height <= 0) {
            throw std::runtime_error("Dimensions invalides dans le fichier : " + filename);
        }

        // Créer la grille avec les dimensions spécifiées
        std::vector<std::vector<bool>> grid(height, std::vector<bool>(width, false));

        // Lecture des états des cellules
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int NEWcellState;
                file >> NEWcellState; //lit l'état de la cellule depuis le fichier et le stocke dans NEWcellState
                grid[y][x] = (NEWcellState == 1);  // 1 pour vivant, 0 pour mort

            }
        }
//if (NEWcellState == 1) {
//    grid[y][x] = true(1); // Si l'état de la cellule est 1, elle devient vivante.
//} else {
//    grid[y][x] = false(0); // Si l'état de la cellule n'est pas 1 (c'est-à-dire 0), elle devient morte.
//}
        file.close(); // Fermer le fichier après lecture
        return grid; // Retourner la grille
    }
    else{
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + filename);
    }
    
}

// Sauvegarde de l'état d'une grille dans un fichier
void FileManager::saveToFile(const std::string& filename, const std::vector<std::vector<bool>>& grid, int width, int height) {
    std::ofstream file(filename);
    if (file.is_open()) {
        // érire les dimensions de la grille
        file << height << " " << width << "\n";
        // écrire l'état des cellules
         //"auto" permet au compilateur de déduire automatiquement le type de row, std::vector<bool>
         //Le "&" signifie qu'on passe row par référence, pour éviter une copie //"const" indique que row ne sera pas modifié pendant l'itération
        for (const auto& row : grid) { // à chaque itération, row contient une ligne de la grille.
            for (bool cell : row) { //pour  chaque élément (cell) de la ligne courante (row).
                file << (cell ? 1 : 0) << " ";
            }
            file << "\n"; //Ajouter un retour à la ligne à la fin de chaque ligne de la grille.
        }
    }

    else {
        throw std::runtime_error("Impossible de sauvegarder dans le fichier : " + filename); //Le throw provoque une interruption immédiate de l'exécution normale du programme (ou de la fonction actuelle)
    }

    file.close();
}
