#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include "Grid.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>


class InputHandler {
public:

    struct Button { bool space, escape, s, r; };

    struct Mouse {
        bool click;
        sf::Vector2i position;
    };

private:
    Button button; //État des boutons clavier
    Mouse mouse;   //État des interactions souris

public:
    InputHandler();

    // Accesseurs
    Button getButtonState(void) const; // Retourne l'état des boutons
    Mouse getMouseState(void) const;  // Retourne l'état de la souris
    // Gestion des événements
    void handleEvent(sf::Event event, sf::RenderWindow& window, Grid& grid, int cellSize);
};


#endif
