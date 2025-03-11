#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics.hpp>
#include "grid.hpp"

class Renderer { // Classe abstraite
protected:
    virtual void render(const Grid& grid) const = 0;
    virtual ~Renderer() = default;
};

class ConsoleRenderer : public Renderer {
public:
    void render(const Grid& grid) const override;
};

class GraphicRenderer : public Renderer {
private:
    sf::RenderWindow& window;
    int cellSize;

public:
    GraphicRenderer(sf::RenderWindow& window, int cellSize);
    void render(const Grid& grid) const override;
};

#endif
