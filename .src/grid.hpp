#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <memory>
#include "Cell.hpp"

class Grid {
private:
    
    std::vector<std::vector<std::unique_ptr<Cell>>> newcells; //L'ensemble des lignes est lui-même stocké dans une std::vector, sorte de tableau en 2d(grille/matrix)
    //Pas besoin de gérer explicitement l'allocation mémoire ou déterminer taille du tableau
public:
    int width, height;
    Grid(int w, int h); //accéder aux éléments en utilisant une syntaxe semblable à celle des matrix (cell[i][j]) cell[i][j] : est une cellule située à la ligne i et la colonne j.
    void initializeRandom();
    int countNeighbors(int x, int y) const;
    void update();
    void toggleCell(int x, int y);

    bool isCellAlive(int x, int y) const;
    std::vector<std::vector<bool>> getStateMatrix() const;

    int getWidth() const;
    int getHeight() const;
};

#endif
