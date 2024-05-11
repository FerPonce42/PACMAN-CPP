#pragma once
#include <SFML/Graphics.hpp>
#include "Jugador.h"
#include "Musica.h"

class Nivel1 {
public:
    Nivel1(sf::RenderWindow& ventana, float ancho, float alto);

    void mostrar();
    void actualizar();
    void manejarEventos();
    bool posicionValida(sf::Vector2f posicion);

private:
    sf::RenderWindow& ventana;
    Musica musicaNivel1;
    sf::Texture fondoTextura;
    sf::Sprite fondoSprite;
    Jugador jugador;
    const int anchoMapa = 30;
    const int altoMapa = 12;
    int** mapa;
    float anchoCelda;
    float altoCelda;
    float posXInicio;
    float posYInicio;
};
