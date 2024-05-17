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

bool Jugador::posicionValida(sf::Vector2f nuevaPosicion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
    float jugadorAncho = sprite.getGlobalBounds().width;
    float jugadorAlto = sprite.getGlobalBounds().height;

    sf::Vector2f esquinas[4] = {
        nuevaPosicion,
        {nuevaPosicion.x + jugadorAncho, nuevaPosicion.y},
        {nuevaPosicion.x, nuevaPosicion.y + jugadorAlto},
        {nuevaPosicion.x + jugadorAncho, nuevaPosicion.y + jugadorAlto}
    };

    for (auto& esquina : esquinas) {
        int columna = static_cast<int>((esquina.x - posXInicio) / anchoCelda);
        int fila = static_cast<int>((esquina.y - posYInicio) / altoCelda);

        if (fila < 0 || fila >= altoMapa || columna < 0 || columna >= anchoMapa || mapa[fila][columna] != 0) {
            return false;
        }
    }

    return true;
}

void Jugador::mover(sf::Vector2f direccion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
    sf::Vector2f nuevaPosicion = sprite.getPosition() + direccion * velocidad;

    if (posicionValida(nuevaPosicion, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
        sprite.setPosition(nuevaPosicion);
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
