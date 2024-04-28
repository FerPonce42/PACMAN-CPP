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

void Jugador::mover(sf::Vector2f direccion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
    // Calculamos la posición a la que intenta moverse el jugador
    sf::Vector2f nuevaPosicion = sprite.getPosition() + direccion * velocidad;

    // Convertir la posición en la ventana a la posición en la matriz del mapa
    int fila = static_cast<int>((nuevaPosicion.y - posYInicio) / altoCelda);
    int columna = static_cast<int>((nuevaPosicion.x - posXInicio) / anchoCelda);

    // Verificar si la nueva posición está dentro de los límites del mapa
    if (fila >= 0 && fila < altoMapa && columna >= 0 && columna < anchoMapa) {
        // Verificar si la nueva posición es un espacio libre en el mapa (valor 0)
        if (mapa[fila][columna] == 0) {
            // Movemos al jugador a la nueva posición
            sprite.move(direccion * velocidad);
        }
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