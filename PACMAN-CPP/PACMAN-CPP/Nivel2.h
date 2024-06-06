#pragma once

#include <SFML/Graphics.hpp>
#include "Jugador.h"
#include "Musica.h"
#include "FantasmaRojo.h"

class Nivel2 {
public:
    Nivel2(sf::RenderWindow& ventana, float ancho, float alto);
    void mostrar();
    void actualizar();
    void manejarEventos();
    bool posicionValida(sf::Vector2f posicion);

private:
    sf::RenderWindow& ventana;
    Musica musicaNivel2;
    sf::Texture fondoTextura;
    sf::Sprite fondoSprite;
    Jugador jugador;
    FantasmaRojo fantasmaRojo;
    std::vector<sf::Sprite> objetos;
    const int anchoMapa = 32;
    const int altoMapa = 13;
    int** mapa;
    float anchoCelda;
    float altoCelda;
    float posXInicio;
    float posYInicio;

    void inicializarMapa();
};