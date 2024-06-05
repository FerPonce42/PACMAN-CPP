#pragma once
#include <SFML/Graphics.hpp>

class Pausa {
public:
    Pausa(sf::RenderWindow& mainWindow); // Constructor
    int mostrar(); // Método para mostrar la pantalla de pausa
    void MoveUp(); // Método para mover la selección hacia arriba
    void MoveDown(); // Método para mover la selección hacia abajo
    int getSelectedOption(); // Método para obtener la opción seleccionada
    bool shouldReturnToMenu(); // Método para verificar si se debe regresar al menú principal

private:
    sf::RenderWindow& window;
    int selectedItemIndex;
    bool returnToMenu;
    sf::Font font;
    sf::Text textoPausa;
    sf::Text reanudarTexto;
    sf::Text salirTexto;
};
