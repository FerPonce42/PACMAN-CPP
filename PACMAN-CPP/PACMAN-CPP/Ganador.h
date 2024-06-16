#pragma once
#include <SFML/Graphics.hpp>

class Ganador {
public:
    Ganador(sf::RenderWindow& mainWindow, int ganador);
    int mostrar();
    void MoveUp();
    void MoveDown();
    int getSelectedOption();

private:
    int selectedItemIndex;
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text textoGanador;
    sf::Text reiniciarTexto;
    sf::Text siguienteNivelTexto;
    sf::Text salirTexto;

    sf::Texture textureJugador1; 
    sf::Texture textureJugador2;
    sf::Sprite fondoSprite;     

    void cargarTexturas(int ganador);

    void Reiniciar();
    void SiguienteNivel();
    void Salir();
};
