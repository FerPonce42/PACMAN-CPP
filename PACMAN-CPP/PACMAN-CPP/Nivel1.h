#pragma once

#include <SFML/Graphics.hpp>
#include "FantasmaRojo.h"
#include "Jugador.h"
#include "Musica.h"
#include "Ganador.h"
#include "Pelotas.h"
#include "Poderes.h"

class Nivel1 {
public:
    Nivel1(sf::RenderWindow& ventana, float ancho, float alto);
    ~Nivel1();
    void mostrar();
    void actualizar();
    void manejarEventos();
    bool posicionValida(sf::Vector2f posicion);
    void verificarColisiones();

private:
    sf::RenderWindow& ventana;
    Musica musicaNivel1;
    sf::Texture fondoTextura;
    sf::Sprite fondoSprite;
    FantasmaRojo fantasmaRojo;
    Jugador jugador;
    Pelotas* pelotas;
    Poderes* poderes;
    std::vector<sf::Sprite> objetos;
    const int anchoMapa = 30;
    const int altoMapa = 12;
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