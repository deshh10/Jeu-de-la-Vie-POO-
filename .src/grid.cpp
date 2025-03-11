#include "Grid.hpp"
#include "cell.hpp"
#include <cstdlib>
#include <ctime>

// Constructeur : initialise une grille vide avec des cellules mortes
Grid::Grid(int w, int h) : width(w), height(h) {
    newcells.resize(height); // ajuste la hauteur de la grille, Si height > taille actuelle: De nouvelles lignes (std::vector<std::unique_ptr<Cell>>) sont ajoutées et initialisées à vide. Si height < , Les lignes excédentaires sont supprimées.
    for (int i = 0; i < height; ++i) {
        newcells[i].resize(width); // Initialiser la largeur...
        for (int j = 0; j < width; ++j) {
            newcells[i][j] = std::make_unique<NormalCell>(false); // Cette fonction crée un objet dynamique (en mémoire libre/heap) de type NormalCell avec l'état initial false (cellule morte). L'objet est alloué dynamiquement et encapsulé dans un std::unique_ptr<Cell>. assigné à newcells.
        }
    }
}

// Initialise la grille avec des cellules vivantes ou mortes aléatoirement
void Grid::initializeRandom() {
    std::srand(std::time(nullptr)); // pour initialiser le générateur avec une graine unique (comme le temps actuel).Sans std::srand, les résultats de std::rand() seront identiques à chaque exécution du programme.Avec std::srand, la séquence devient différente à chaque exécution.
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            newcells[i][j] = std::make_unique<NormalCell>(std::rand() % 2 == 0); // Vivant ou mort aléatoire(std::rand() retourne un nombre entier pseudo-aléatoire, % 2 (modulo 2) réduit cet entier à un reste après division par 2. Le résultat est toujours 0 ou 1)
        }
    }
}

// Compte le nombre de voisins vivants d'une cellule donnée
int Grid::countNeighbors(int x, int y) const {
    int count = 0;
    for (int i = -1; i <= 1; ++i) { //Parcourir le voisinage d'une cellule
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue; // Ne pas compter la cellule elle-même

            // Calculer les coordonnées des voisins en gérant les bords de manière torique
            int nx = (x + i + height) % height;//x + i calcule la ligne du voisin//+ height gère les cas où (x + i) est négatif.//% height ramène l'indice dans l'intervalle [0, height-1].
            int ny = (y + j + width) % width;
            
            if (newcells[nx][ny]->isAlive()) { // Vérifie si la cellule située aux coordonnées (nx, ny) est vivante.(Coordonnées du voisin calculées avec la gestion torique.)
                count++;//Incrémente le compteur si le voisin est vivant.
            }
        }
    }

    return count;//Une fois que toutes les cellules autour de (x, y) ont été vérifiées, la fonction retourne le nombre total de voisins vivants.
//Ce nombre est utilisé pour appliquer les règles du jeu de la vie :
//Une cellule vivante reste vivante si elle a 2 ou 3 voisins vivants.
//Une cellule morte devient vivante si elle a exactement 3 voisins vivants.

}

// Met à jour l'état de la grille en appliquant les règles du jeu de la vie
void Grid::update() {
    // Nouvelle grille pour stocker les états suivants
    std::vector<std::vector<std::unique_ptr<Cell>>> nextgrid(height);//créer une nouvelle version de la grille après une étape du jeu de la vie. Ici, chaque élément est un std::unique_ptr<Cell>.

    for (int i = 0; i < height; ++i) {
        nextgrid[i].resize(width);
        for (int j = 0; j < width; ++j) {
            //get() : Retourne un pointeur brut (Cell*) à partir du std::unique_ptr<Cell>.
            if (dynamic_cast<ObstacleCell*>(newcells[i][j].get())) { // vérifie si la cellule actuelle (cells[i][j]) est une "ObstacleCell" avec dynamic_cast, si oui on traite la cellule comme tel
            //Essaie de convertir ce pointeur brut en un pointeur de type ObstacleCell*.
            //Si la conversion réussit, cela signifie que la cellule est bien une ObstacleCell.
            //Si la conversion échoue, cela retourne nullptr. Si la cellule est une ObstacleCell, on entre dans le bloc if.   
               
                // Conserver l'obstacle tel quel
                nextgrid[i][j] = std::make_unique<ObstacleCell>();//Conserve les obstacles dans la nouvelle grille : Recrée une nouvelle instance d'ObstacleCell aux mêmes positions.
            } else {
                // Appliquer les règles pour une cellule normale
                int neighbors = countNeighbors(i, j);
                //copier ou transférer l’état actuel des cellules d'une grille newcells dans une nouvelle grille temporaire nextGrid, tout en créant de nouvelles instances dynamiques de cellules (NormalCell). L’état vivant/mort des cellules est préservé grâce à la méthode isAlive().
                nextgrid[i][j] = std::make_unique<NormalCell>(newcells[i][j]->isAlive());//std::make_unique<NormalCell>(...)Crée une nouvelle instance dynamique de NormalCell, initialisée avec l’état retourné par isAlive().
                nextgrid[i][j]->updateState(neighbors);
            }
        }
    }

    // Remplacer la grille actuelle par la nouvelle version
    newcells = std::move(nextgrid);//la grille actuelle est remplacé par nextgrid avec les newcells
}

// Inverse l'état d'une cellule normale
void Grid::toggleCell(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        if (dynamic_cast<NormalCell*>(newcells[y][x].get())) {
            newcells[y][x]->updateState(newcells[y][x]->isAlive() ? 0 : 3); // Basculer entre vivant et mort
        }
    }
}

// Retourne si une cellule est vivante
bool Grid::isCellAlive(int x, int y) const {
    return newcells[y][x]->isAlive();
}

// Retourne une version booléenne de l'état des cellules (utile pour la sauvegarde)
std::vector<std::vector<bool>> Grid::getStateMatrix() const {
//Chaque ligne est un std::vector<bool>.L'ensemble des lignes est stocké dans un std::vector.
    std::vector<std::vector<bool>> matrix(height, std::vector<bool>(width));//ligne(width) initialisé a fals
//Pour chaque ligne, on utilise std::vector<bool>(width) :Crée un vecteur contenant width booléens. Tous ces booléens sont initialisés à leur valeur par défaut, qui est false.
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            matrix[i][j] = newcells[i][j]->isAlive(); //  met à jour la cellule [i][j] de la matrice booléenne matrix avec l’état vivant/mort de la cellule correspondante dans newCells. 
        } //->isAlive() <=> selon l'état(vivant ou mort)
    }

    return matrix;
}

int Grid::getWidth() const {
    return width;
}

int Grid::getHeight() const {
    return height;
}
