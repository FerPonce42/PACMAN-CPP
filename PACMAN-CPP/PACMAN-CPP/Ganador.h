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

    //void Reiniciar();   CUANTO ESTEN LISTOS LOS DEMAS NIVELES, HABILITARLOS DESDE EEL MAIN
    //void SiguienteNivel();
    //void Salir();
};
