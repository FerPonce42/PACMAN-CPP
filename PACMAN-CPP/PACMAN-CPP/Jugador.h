#pragma once
#include <SFML/Graphics.hpp>

class Jugador {
public:
    Jugador(float x, float y, float velocidad);

    void mover(sf::Vector2f direccion);
    void dibujar(sf::RenderWindow& ventana);

private:
    sf::RectangleShape forma;
    float velocidad;
};