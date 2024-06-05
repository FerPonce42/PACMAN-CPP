#pragma once
#include <SFML/Graphics.hpp>

class Pausa {
public:
    Pausa(sf::RenderWindow& mainWindow); // Constructor
    int mostrar(); // M�todo para mostrar la pantalla de pausa
    void MoveUp(); // M�todo para mover la selecci�n hacia arriba
    void MoveDown(); // M�todo para mover la selecci�n hacia abajo
    int getSelectedOption(); // M�todo para obtener la opci�n seleccionada
    bool shouldReturnToMenu(); // M�todo para verificar si se debe regresar al men� principal

private:
    sf::RenderWindow& window;
    int selectedItemIndex;
    bool returnToMenu;
    sf::Font font;
    sf::Text textoPausa;
    sf::Text reanudarTexto;
    sf::Text salirTexto;
};
