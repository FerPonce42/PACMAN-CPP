#include "Jugador.h"
#include <iostream>

Jugador::Jugador(float x, float y, float velocidad) : velocidad(velocidad) {
    if (!textura.loadFromFile("Nivel1/derecha.png")) {
        // Manejar el error si no se puede cargar la textura
        std::cerr << "Error al cargar la textura del jugador." << std::endl;
    }

    sprite.setTexture(textura);
    sprite.setPosition(x, y);

    sprite.setScale(1.0f, 1.0f); // TAMAÑO DEL JUGADOR
}

void Jugador::mover(sf::Vector2f direccion) {
    sprite.move(direccion * velocidad);
}

void Jugador::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(sprite);
}

void Jugador::cambiarTextura(const std::string& archivoTextura) {
    if (!textura.loadFromFile("Nivel1/" + archivoTextura)) {
        // Manejar el error si no se puede cargar la nueva textura
        std::cerr << "Error al cargar la nueva textura del jugador." << std::endl;
    }

    sprite.setTexture(textura);
}

void Jugador::setDireccion(sf::Vector2f nuevaDireccion) {
    direccion = nuevaDireccion;
}

sf::Vector2f Jugador::getPosicion() const {
    return sprite.getPosition();
}
