#include "InputHandler.hpp"

using namespace sf;
// Constructeur : Initialise tous les états à `false`
InputHandler::InputHandler() {
    button.space,button.escape, mouse.click, button.s = false,
    mouse.position = {0, 0};
}

// Retourne l'état des boutons
InputHandler::Button InputHandler::getButtonState(void) const {
    return button;
}

// Retourne l'état de la souris
InputHandler::Mouse InputHandler::getMouseState(void) const {
    return mouse;
}

// Gestion des événements
void InputHandler::handleEvent(Event event, RenderWindow& window, Grid& grid, int cellSize) {
    // Fermer la fenêtre si l'utilisateur clique sur "Fermer"
    if (event.type == Event::Closed) {
        window.close();
    }

    // Gestion des touches du clavier
    if (event.type == Event::KeyPressed) {
        switch (event.key.code) {
            case Keyboard::Space: // Pause ou reprise
                button.space = !button.space;
                break;
            
            case Keyboard::S: //sauvegarder
                button.s = true;
                break;

            case Keyboard::Escape: // quitter
                button.escape = true;
                break;

            case Keyboard::R: //reset
                button.r = true;

            default:
                break;
        }
    }

    // Réinitialisation des boutons lorsqu'ils sont relâchés
    if (event.type == Event::KeyReleased) {
        switch (event.key.code) {

            case Keyboard::Escape:
                button.escape = false;
                break;
            
            case Keyboard::S: 
                button.s = false;
                break;

            case Keyboard::R:
                button.r= false;

            default:
                break;
        }
    }
   
    // Gestion des clics de souris
    if (event.type == sf::Event::MouseButtonPressed) {
        mouse.click = true;
        mouse.position = sf::Mouse::getPosition(window);

        // Calculer la cellule cliquée
        int x = mouse.position.x / cellSize;
        int y = mouse.position.y / cellSize;

        // Inverser l'état de la cellule si les coordonnées sont valides
        if (x >= 0 && x < grid.getWidth() && y >= 0 && y < grid.getHeight()) {
            grid.toggleCell(x, y);
        }

    }
    

    // Réinitialisation du clic gauche
    if (event.type == sf::Event::MouseButtonReleased) {
        mouse.click = false;
    }
}
