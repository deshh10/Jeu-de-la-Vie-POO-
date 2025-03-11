//g++ -o game .src/main.cpp .src/renderer.cpp .src/inputhandler.cpp .src/grid.cpp .src/FileManager.cpp .src/GameManager.cpp .src/cell.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
#include "GameManager.hpp"
#include "FileManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include "grid.hpp"


int main() {
    int width = 50, height = 30, cellSize = 20;

    // Création du gestionnaire de jeu
    GameManager gameManager(width, height, cellSize);

    // Choix du mode d'exécution
    std::cout << "Choisissez le mode : (1) Console, (2) Graphique : ";
    int mode;
    std::cin >> mode;

    // Exécution du jeu selon le mode choisi
    if (mode == 1) {
        // Mode console
        gameManager.runConsoleMode();
    } else if (mode == 2) {
        // Mode graphique
        gameManager.runGraphiqueMode();
    } else {
        // Si le mode est invalide, afficher une erreur
        std::cerr << "Mode invalide. Fin du programme." << std::endl;
    }

    return 0;
}
