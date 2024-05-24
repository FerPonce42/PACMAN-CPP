#include "FantasmaRojo.h"
#include <iostream>
#include <cmath>

FantasmaRojo::FantasmaRojo(const std::string& rutaTextura, float posX, float posY, float velocidad)
    : velocidad(velocidad), indiceCamino(0), pathfinding(nullptr) {
    if (!textura.loadFromFile("Nivel1/fantasmarojo.png")) {
        std::cerr << "Error al cargar la textura del fantasma." << std::endl;
    }
    sprite.setTexture(textura);
    sprite.setPosition(740, 500);
    sprite.setScale(0.8f, 0.8f);
}

void FantasmaRojo::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(sprite);
}

void FantasmaRojo::mover(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio, sf::Vector2f posJugador) {
    if (!pathfinding) {
        pathfinding = new Pathfinding(mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
    }

    if (camino.empty() || indiceCamino >= camino.size()) {
        actualizarCamino(posJugador);
    }

    if (indiceCamino < camino.size()) {
        sf::Vector2f nuevaPosicion = camino[indiceCamino];
        if (posicionValida(nuevaPosicion, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
            sprite.setPosition(nuevaPosicion);
            indiceCamino++;
        }
    }
}

void FantasmaRojo::actualizarCamino(sf::Vector2f posJugador) {
    camino = pathfinding->encontrarCamino(sprite.getPosition(), posJugador);
    indiceCamino = 0;
}

sf::Vector2f FantasmaRojo::getPosicion() const {
    return sprite.getPosition();
}

bool FantasmaRojo::posicionValida(sf::Vector2f posicion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
    float fantasmaAncho = sprite.getGlobalBounds().width;
    float fantasmaAlto = sprite.getGlobalBounds().height;

    int celdaX = (posicion.x - posXInicio) / anchoCelda;
    int celdaY = (posicion.y - posYInicio) / altoCelda;

    if (celdaX < 0 || celdaX >= anchoMapa || celdaY < 0 || celdaY >= altoMapa) {
        return false;
    }

    return mapa[celdaY][celdaX] == 0;
}
