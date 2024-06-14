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

    sf::Texture textureJugador1;  // Textura para jugador 1
    sf::Texture textureJugador2;  // Textura para jugador 2
    sf::Sprite fondoSprite;       // Sprite para mostrar la textura de fondo

    void cargarTexturas(int ganador);

    //void Reiniciar();   CUANTO ESTEN LISTOS LOS DEMAS NIVELES, HABILITARLOS DESDE EEL MAIN
    //void SiguienteNivel();
    //void Salir();
};
