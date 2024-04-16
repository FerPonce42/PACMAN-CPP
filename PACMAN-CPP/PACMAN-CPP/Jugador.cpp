#include "Jugador.h"
#include <iostream>

Jugador::Jugador(float x, float y, float velocidad) : velocidad(velocidad) {
    forma.setSize(sf::Vector2f(40, 40)); 
    forma.setPosition(x, y);
    forma.setFillColor(sf::Color::Yellow);
}

void Jugador::mover(sf::Vector2f direccion) {
    forma.move(direccion * velocidad);
}

void Jugador::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(forma);
}