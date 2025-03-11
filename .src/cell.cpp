#include "cell.hpp"

NormalCell::NormalCell(bool alive) : state(alive) {}

bool NormalCell::isAlive() const {
    return state; // Retourne l'état de la cellule
}

void NormalCell::updateState(int neighbors) {
    if (state) {
        // Une cellule vivante reste vivante si elle a 2 ou 3 voisins
        state = (neighbors == 2 || neighbors == 3);
    } else {
        // Une cellule morte devient vivante si elle a exactement 3 voisins
        state = (neighbors == 3);
    }
}

bool ObstacleCell::isAlive() const {
    return false; // Une cellule obstacle est toujours morte
}

void ObstacleCell::updateState(int neighbors) {
    // Pas de mise à jour : les cellules obstacles ne changent jamais d'état
}
