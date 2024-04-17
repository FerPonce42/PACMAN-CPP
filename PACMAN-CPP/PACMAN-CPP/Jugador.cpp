#include "Jugador.h"
#include <iostream>

Jugador::Jugador(float x, float y, float velocidad) : velocidad(velocidad) {
    if (!textura.loadFromFile("Nivel1/derecha.png")) {
        
    }

    sprite.setTexture(textura);
    sprite.setPosition(x, y);

   
    sprite.setScale(2.0f, 2.0f); // TAMAÑO DEL JUGADORR
}

void Jugador::mover(sf::Vector2f direccion) {
    sprite.move(direccion * velocidad);
}

void Jugador::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(sprite);
}

void Jugador::cambiarTextura(const std::string& archivoTextura) {
    if (!textura.loadFromFile("Nivel1/" + archivoTextura)) {
        
    }

    sprite.setTexture(textura);
}