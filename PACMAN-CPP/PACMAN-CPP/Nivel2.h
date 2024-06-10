#pragma once

#include <SFML/Graphics.hpp>
#include "FantasmaJugador.h"
#include "PacmanIA.h"
#include "Musica.h"
#include "Ganador.h"
#include "Pelotas.h"
#include "Poderes.h"

class Nivel2 {
public:
    Nivel2(sf::RenderWindow& ventana, float ancho, float alto);
    ~Nivel2();
    void mostrar();
    void actualizar();
    void manejarEventos();
    bool posicionValida(sf::Vector2f posicion);
    void verificarColisiones();

private:
    sf::RenderWindow& ventana;
    Musica musicaNivel2;
    sf::Texture fondoTextura;
    sf::Sprite fondoSprite;
    FantasmaJugador fantasmaJugador;
    PacmanIA pacmanIA;
    Pelotas* pelotas;
    Poderes* poderes;
    std::vector<sf::Sprite> objetos;
    const int anchoMapa = 32;
    const int altoMapa = 13;
    int** mapa;
    float anchoCelda;
    float altoCelda;
    float posXInicio;
    float posYInicio;

    sf::Font font;
    sf::Text textoContador;
    sf::Clock relojContador;

    void inicializarMapa();
};
