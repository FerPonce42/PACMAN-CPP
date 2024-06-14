#pragma once
#include <SFML/Graphics.hpp>

class Creditos {
public:
    Creditos(sf::RenderWindow& mainWindow);
    int mostrar();
    bool shouldReturnToMenu();

private:
    sf::RenderWindow& window;
    bool returnToMenu;
    sf::Font font;
    sf::Text regresarTexto;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    void handleInput();
};
