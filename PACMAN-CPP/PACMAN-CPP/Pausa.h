#pragma once
#include <SFML/Graphics.hpp>

class Pausa {
public:
    Pausa(sf::RenderWindow& mainWindow);
    int mostrar();
    void MoveUp();
    void MoveDown();
    int getSelectedOption();
    bool shouldReturnToMenu();

private:
    sf::RenderWindow& window;
    int selectedItemIndex;
    bool returnToMenu;
    sf::Font font;
    sf::Text textoPausa;
    sf::Text reanudarTexto;
    sf::Text salirTexto;
    sf::Texture backgroundTexture;  
    sf::Sprite backgroundSprite;    
};
