#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include "grid.hpp"

class GameManager
{
private:
    Grid grid;
    int cellSize;
    bool isPaused = false;
    void checkButtons();
    void setupConfigurationMenu(); // Méthode pour configurer le menu graphique
    sf::Texture backgroundTexture; 
    sf::Sprite backgroundSprite;


public:
    GameManager(int width, int height, int cellSize);
    void runConsoleMode();
    void runGraphiqueMode();
};

#endif
