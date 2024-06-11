#include "FantasmaRosa.h"

FantasmaRosa::FantasmaRosa(float x, float y, float velocidad)
    : FantasmaRojo(x, y, velocidad) {
    animacion->limpiarFrames();
    animacion->agregarFrame("Nivel1/Fantasmas/Rosa/derecha1.png");
    animacion->agregarFrame("Nivel1/Fantasmas/Rosa/derecha2.png");
    animacion->agregarFrame("Nivel1/Fantasmas/Rosa/derecha3.png");

    sprite.setPosition(715, 520);
    sprite.setScale(0.8f, 0.8f);
}

void FantasmaRosa::setPosicionInicial() {
    sprite.setPosition(715, 520);
}

void FantasmaRosa::moverAI(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio, sf::Vector2f playerPosition, bool powerActive) {
    if (powerActive && !poderActivo) {
        poderActivo = true;
        cambiarTexturaPorPoder();
    }
    else if (!powerActive && poderActivo) {
        poderActivo = false;
        animacion->limpiarFrames();
        animacion->agregarFrame("Nivel1/Fantasmas/Rosa/derecha1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rosa/derecha2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rosa/derecha3.png");
    }

    if (poderActivo) {
        avoidPlayer(playerPosition, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
    }
    else {
        chasePlayer(playerPosition, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
    }

    mover(direccionActual, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
}

void FantasmaRosa::setDireccion(sf::Vector2f nuevaDireccion) {
    direccion = nuevaDireccion;

    animacion->limpiarFrames();

    if (direccion.x > 0) {
        animacion->agregarFrame("Nivel1/Fantasmas/Rosa/derecha1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rosa/derecha2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rosa/derecha3.png");
    }
    else if (direccion.x < 0) {
        animacion->agregarFrame("Nivel1/Fantasmas/Rosa/izquierda1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rosa/izquierda2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rosa/izquierda3.png");
    }
    else if (direccion.y > 0) {
        animacion->agregarFrame("Nivel1/Fantasmas/Rosa/abajo1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rosa/abajo2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rosa/abajo3.png");
    }
    else if (direccion.y < 0) {
        animacion->agregarFrame("Nivel1/Fantasmas/Rosa/arriba1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rosa/arriba2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rosa/arriba3.png");
    }
}
