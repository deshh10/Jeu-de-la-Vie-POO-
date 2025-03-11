#include "GameManager.hpp"
#include "renderer.hpp"
#include "FileManager.hpp"
#include "inputhandler.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

sf::RenderWindow window;
InputHandler inputHandler; 

GameManager::GameManager(int width, int height, int cellSize) 
    : grid(width, height), cellSize(cellSize) {}

void GameManager::checkButtons() {
    if (inputHandler.getButtonState().escape) {
        window.close();
    }

    if (inputHandler.getButtonState().s) {
        FileManager::saveToFile("config.txt", grid.getStateMatrix(), grid.getWidth(), grid.getHeight());
        std::cout << "Configuration sauvegardée dans 'config.txt'\n";
    }

    if (inputHandler.getButtonState().r){
        for (int y = 0; y < grid.height; ++y) {
                for (int x = 0; x < grid.width; ++x) {
                     if(grid.isCellAlive(x,y)){
                        grid.toggleCell(x, y);
                     }
                }
            }
    }
}

void GameManager::setupConfigurationMenu() {

    // Création de la fenêtre
    window.create(sf::VideoMode(grid.getWidth() * cellSize, grid.getHeight() * cellSize), "Jeu de la Vie");
    backgroundSprite.setTexture(backgroundTexture);

    // Récupération des tailles
    sf::Vector2u textureSize = backgroundTexture.getSize(); // Taille de la texture
    sf::Vector2u windowSize = window.getSize();             // Taille de la fenêtre

    // Calcul du facteur d'échelle
    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    // Ajustement de l'échelle du sprite
    backgroundSprite.setScale(scaleX, scaleY);

    sf::Font font;
    if (!font.loadFromFile("Corporation Games.otf")) {
        std::cerr << "Erreur : Impossible de charger la police.\n";
        return;
    }

    sf::Text message("Voulez-vous charger une configuration existante ?", font, 24);
    sf::FloatRect messageBounds = message.getGlobalBounds();
    message.setPosition(
        (window.getSize().x - messageBounds.width) / 2,
        window.getSize().y / 4
    );

    sf::RectangleShape buttonYes(sf::Vector2f(150, 50));
    buttonYes.setFillColor(sf::Color::Green);
    buttonYes.setPosition(
        (window.getSize().x / 2) - 175,
        window.getSize().y / 2
    );

    sf::Text textYes("O", font, 24);
    sf::FloatRect textYesBounds = textYes.getGlobalBounds();
    textYes.setPosition(
        buttonYes.getPosition().x + (buttonYes.getSize().x - textYesBounds.width) / 2,
        buttonYes.getPosition().y + (buttonYes.getSize().y - textYesBounds.height) / 2
    );

    sf::RectangleShape buttonNo(sf::Vector2f(150, 50));
    buttonNo.setFillColor(sf::Color::Red);
    buttonNo.setPosition(
        (window.getSize().x / 2) + 25,
        window.getSize().y / 2
    );

    sf::Text textNo("N", font, 24);
    sf::FloatRect textNoBounds = textNo.getGlobalBounds();
    textNo.setPosition(
        buttonNo.getPosition().x + (buttonNo.getSize().x - textNoBounds.width) / 2,
        buttonNo.getPosition().y + (buttonNo.getSize().y - textNoBounds.height) / 2
    );

    bool selectionMade = false;
    bool loadConfig = false;
        while (!selectionMade && window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (buttonYes.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        loadConfig = true;
                        selectionMade = true;
                    } else if (buttonNo.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        selectionMade = true;
                    }
                }
            }
        
            window.clear();
            window.draw(backgroundSprite); // L'image est dessinée ici pendant le menu
            window.draw(message);
            window.draw(buttonYes);
            window.draw(buttonNo);
            window.draw(textYes);
            window.draw(textNo);
            window.display();
        
        }
    


    // Charger ou initialiser la grille
    
    window.display();
    try {
        if (loadConfig) {
            
            int choix =6;
             const int numButtons = 5;
    sf::RectangleShape buttons[numButtons];
    sf::Text texts[numButtons];
    const float buttonWidth = 100.f;
    const float buttonHeight = 50.f;
    const float spacing = 20.f; // Space between buttons
    const float startX = (window.getSize().x - (numButtons * buttonWidth + (numButtons - 1) * spacing)) / 2.f;
    const float startY = window.getSize().y / 2.f - buttonHeight / 2.f;

    for (int i = 0; i < numButtons; ++i) {
        // Configure button
        buttons[i].setSize(sf::Vector2f(buttonWidth, buttonHeight));
        buttons[i].setFillColor(sf::Color::Blue);
        buttons[i].setPosition(startX + i * (buttonWidth + spacing), startY);

        // Configure text
        texts[i].setFont(font);
        texts[i].setString(std::to_string(i + 1));
        texts[i].setCharacterSize(24);
        texts[i].setFillColor(sf::Color::White);

        // Center text in button
        sf::FloatRect textBounds = texts[i].getGlobalBounds();
        texts[i].setPosition(
            buttons[i].getPosition().x + (buttonWidth - textBounds.width) / 2.f,
            buttons[i].getPosition().y + (buttonHeight - textBounds.height) / 2.f
        );
    }

    while (window.isOpen() && choix == 6) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();}
            if (event.type == sf::Event::MouseButtonPressed) {
    sf::Vector2i mousePoses = sf::Mouse::getPosition(window);
    std::cout << "Mouse position: " << mousePoses.x << ", " << mousePoses.y << std::endl;
    for (int j = 0; j < numButtons; ++j) {
        if (buttons[j].getGlobalBounds().contains(mousePoses.x, mousePoses.y)) {
            choix = j;
            break;
        }
    }
}
        }

        window.clear();
        for (int i = 0; i < numButtons; ++i) {
            window.draw(buttons[i]);
            window.draw(texts[i]);
        }
        window.display();
    }

    if (choix == 0 ){
             int fileWidth, fileHeight;
            auto stateMatrix = FileManager::loadFromFile("config1.txt", fileWidth, fileHeight);
            grid = Grid(fileWidth, fileHeight);
            for (int y = 0; y < fileHeight; ++y) {
                for (int x = 0; x < fileWidth; ++x) {
                    if (stateMatrix[y][x]) {
                        grid.toggleCell(x, y);
                    }
                }
    }std::cout << "Configuration chargée depuis 'config1.txt'.\n";
    } else if (choix == 1) {
             int fileWidth, fileHeight;
            auto stateMatrix = FileManager::loadFromFile("config2.txt", fileWidth, fileHeight);
            grid = Grid(fileWidth, fileHeight);
            for (int y = 0; y < fileHeight; ++y) {
                for (int x = 0; x < fileWidth; ++x) {
                    if (stateMatrix[y][x]) {
                        grid.toggleCell(x, y);
                    }
                }
    } std::cout << "Configuration chargée depuis 'config2.txt'.\n";
    }else if (choix == 2) {
             int fileWidth, fileHeight;
            auto stateMatrix = FileManager::loadFromFile("config3.txt", fileWidth, fileHeight);
            grid = Grid(fileWidth, fileHeight);
            for (int y = 0; y < fileHeight; ++y) {
                for (int x = 0; x < fileWidth; ++x) {
                    if (stateMatrix[y][x]) {
                        grid.toggleCell(x, y);
                    }
                }
    } std::cout << "Configuration chargée depuis 'config3.txt'.\n";
    }else if (choix == 3) {
             int fileWidth, fileHeight;
            auto stateMatrix = FileManager::loadFromFile("config4.txt", fileWidth, fileHeight);
            grid = Grid(fileWidth, fileHeight);
            for (int y = 0; y < fileHeight; ++y) {
                for (int x = 0; x < fileWidth; ++x) {
                    if (stateMatrix[y][x]) {
                        grid.toggleCell(x, y);
                    }
                }
    }
            std::cout << "Configuration chargée depuis 'config4.txt'.\n";}
            else if (choix == 4) {
             int fileWidth, fileHeight;
            auto stateMatrix = FileManager::loadFromFile("config.txt", fileWidth, fileHeight);
            grid = Grid(fileWidth, fileHeight);
            for (int y = 0; y < fileHeight; ++y) {
                for (int x = 0; x < fileWidth; ++x) {
                    if (stateMatrix[y][x]) {
                        grid.toggleCell(x, y);
                    }
                }
    }
            std::cout << "Configuration chargée depuis 'config.txt'.\n";}
        } else {
            
            grid.initializeRandom();
            std::cout << "Grille initialisée aléatoirement.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors du chargement : " << e.what() << '\n';
        
        grid.initializeRandom();
        
    }
}


void GameManager::runConsoleMode() {
    ConsoleRenderer consoleRenderer;
    bool isRunning = true;

    // Intégration de la logique de choix de configuration
    std::cout << "Voulez-vous charger une configuration existante ? (o/n) ";
    char charger;
    std::cin >> charger;

    try {
        if (charger == 'o' || charger == 'O') {
            int fileWidth, fileHeight;
            // Charger la grille depuis un fichier
            // "auto" pour déterminer automatiquement le type de la variable stateMatrix en fonction du type de retour de la fonction FileManager::loadFromFile()
            auto stateMatrix = FileManager::loadFromFile("config.txt", fileWidth, fileHeight);

            // Redimensionner et initialiser la grille
            grid = Grid(fileWidth, fileHeight); 
            for (int y = 0; y < fileHeight; ++y) {
                for (int x = 0; x < fileWidth; ++x) {
                    if (stateMatrix[y][x]) {
                        grid.toggleCell(x, y); // Activer la cellule si elle est vivante vue que elle sont tous morte par défaut dans la grille
                    }
                }
            }
            
            std::cout << "Configuration chargée depuis 'config.txt'.\n";
        } else if (charger == 'n' || charger == 'N') {
            grid.initializeRandom(); // Initialisation aléatoire
            std::cout << "Grille initialisée aléatoirement.\n";
        } else {
            std::cerr << "Entrée invalide. Grille initialisée aléatoirement par défaut.\n";
            grid.initializeRandom();
        }
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors du chargement : " << e.what() << '\n';
        std::cerr << "Initialisation aléatoire par défaut.\n";
        grid.initializeRandom();
    }

    // Boucle principale
    while (isRunning) {
        system("clear"); // Efface le terminal pour réafficher la grille
        consoleRenderer.render(grid);
        grid.update();

        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Pause de 500 ms
    }
}


void GameManager::runGraphiqueMode() {
    
    // Créer un objet sf::Music
    sf::Music music;

    // Charger la musique à partir d'un fichier (par exemple "music.ogg")
    if (!music.openFromFile("music.ogg")) {
    std::cerr << "Erreur : Impossible de charger la musique.\n";
    return;
    }

    // Jouer la musique
    music.play();

    // Vous pouvez aussi ajuster le volume, la boucle, etc. :
    music.setVolume(50); // Réglez le volume entre 0 et 100
    music.setLoop(true);  // Pour faire en sorte que la musique se répète en boucle
    // Chargement de l'image de fond

    // Chargement de l'image de fond
    if (!backgroundTexture.loadFromFile("photo.jpg")) {
        std::cerr << "Erreur : Impossible de charger l'arrière-plan.\n";
        return;
    }
    
    setupConfigurationMenu();
    
    GraphicRenderer graphicRenderer(window, cellSize);
    bool isPaused = false;

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            inputHandler.handleEvent(event, window, grid, cellSize);
            isPaused = inputHandler.getButtonState().space;
        }
        checkButtons();

        if (!isPaused) {
            grid.update();
            sf::sleep(sf::milliseconds(200));
        }
        music.stop();
        window.clear();
        window.draw(backgroundSprite);
        graphicRenderer.render(grid);
        window.display();
    }
}
