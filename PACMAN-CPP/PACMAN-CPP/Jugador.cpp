#include "Jugador.h"
#include <iostream>

Jugador::Jugador(float x, float y, float velocidad) : velocidad(velocidad) {
    if (!textura.loadFromFile("Nivel1/derecha.png")) {
        std::cerr << "Error al cargar la textura del jugador." << std::endl;
    }

    sprite.setTexture(textura);
    sprite.setPosition(x, y);

    sprite.setScale(1.0f, 1.0f); // TAMAÑO DEL JUGADOR
}

void Jugador::mover(sf::Vector2f direccion, const std::vector<sf::Sprite>& objetos) {
    // Calculamos la posición a la que intenta moverse el jugador
    sf::Vector2f nuevaPosicion = sprite.getPosition() + direccion * velocidad;

    // Verificar colisiones con los objetos
    bool colision = false;
    for (const auto& objeto : objetos) {
        if (sprite.getGlobalBounds().intersects(objeto.getGlobalBounds())) {
            colision = true;
            break;
        }
    }

    // Verificar si la nueva posición no colisiona con ningún objeto
    if (!colision) {
        // Movemos al jugador a la nueva posición
        sprite.move(direccion * velocidad);
    }
}

void Jugador::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(sprite);
}

void Jugador::cambiarTextura(const std::string& archivoTextura) {
    if (!textura.loadFromFile("Nivel1/" + archivoTextura)) {
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
