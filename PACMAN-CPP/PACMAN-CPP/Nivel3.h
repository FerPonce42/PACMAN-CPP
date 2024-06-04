#pragma once

#include <SFML/Graphics.hpp>
#include "Jugador1.h"
#include "Jugador2.h"
#include "Musica.h"

class Nivel3 {
public:
    Nivel3(sf::RenderWindow& ventana, float ancho, float alto);
    void mostrar();
    void actualizar();
    void manejarEventos();
    bool posicionValida(sf::Vector2f posicion);

private:
    sf::RenderWindow& ventana;
    Musica musicaNivel3;
    sf::Texture fondoTextura;
    sf::Sprite fondoSprite;
    Jugador1 jugador1;
    Jugador2 jugador2;
    std::vector<sf::Sprite> objetos;
    const int anchoMapa = 30;
    const int altoMapa = 12;
    int** mapa;
    float anchoCelda;
    float altoCelda;
    float posXInicio;
    float posYInicio;

    void inicializarMapa();
};