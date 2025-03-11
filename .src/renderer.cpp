#include "Renderer.hpp"
#include <iostream>



void ConsoleRenderer::render(const Grid& grid) const {
    for (int y = 0; y < grid.getHeight(); ++y) {
        for (int x = 0; x < grid.getWidth(); ++x) {
            std::cout << (grid.isCellAlive(x, y) ? 1 : 0) << " "; // Vérifie si la cellule est vivante et affiche 1, sinon 0
        }
        std::cout <<std::endl;
    }
}

GraphicRenderer::GraphicRenderer(sf::RenderWindow& window, int cellSize) : window(window), cellSize(cellSize) {}

void GraphicRenderer::render(const Grid& grid) const {
    
    for (int i = 0; i < grid.getHeight(); ++i) {
        for (int j = 0; j < grid.getWidth(); ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize - 1, cellSize - 1));
            //utiliser la fonction...thickness
            cell.setPosition(j * cellSize, i * cellSize);
            cell.setFillColor(grid.isCellAlive(j, i) ? sf::Color::White : sf::Color::Transparent);
            window.draw(cell);
        }
    }
}
