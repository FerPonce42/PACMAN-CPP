#include "FantasmaCeleste.h"

FantasmaCeleste::FantasmaCeleste(float x, float y, float velocidad)
    : FantasmaRojo(x, y, velocidad) {
    animacion->limpiarFrames();
    animacion->agregarFrame("Nivel1/Fantasmas/Celeste/derecha1.png");
    animacion->agregarFrame("Nivel1/Fantasmas/Celeste/derecha2.png");
    animacion->agregarFrame("Nivel1/Fantasmas/Celeste/derecha3.png");

    sprite.setPosition(755, 520); // FANTASMA CELESTE
    sprite.setScale(0.8f, 0.8f);
}

void FantasmaCeleste::setPosicionInicial() {
    sprite.setPosition(755, 520);
}

void FantasmaCeleste::moverAI(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio, sf::Vector2f playerPosition, bool powerActive) {
    if (powerActive && !poderActivo) {
        poderActivo = true;
        cambiarTexturaPorPoder();
    }
    else if (!powerActive && poderActivo) {
        poderActivo = false;
        animacion->limpiarFrames();
        animacion->agregarFrame("Nivel1/Fantasmas/Celeste/derecha1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Celeste/derecha2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Celeste/derecha3.png");
    }

    if (poderActivo) {
        avoidPlayer(playerPosition, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
    }
    else {
        chasePlayer(playerPosition, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
    }

    mover(direccionActual, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
}

void FantasmaCeleste::setDireccion(sf::Vector2f nuevaDireccion) {
    direccion = nuevaDireccion;

    animacion->limpiarFrames();

    if (direccion.x > 0) {
        animacion->agregarFrame("Nivel1/Fantasmas/Celeste/derecha1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Celeste/derecha2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Celeste/derecha3.png");
    }
    else if (direccion.x < 0) {
        animacion->agregarFrame("Nivel1/Fantasmas/Celeste/izquierda1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Celeste/izquierda2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Celeste/izquierda3.png");
    }
    else if (direccion.y > 0) {
        animacion->agregarFrame("Nivel1/Fantasmas/Celeste/abajo1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Celeste/abajo2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Celeste/abajo3.png");
    }
    else if (direccion.y < 0) {
        animacion->agregarFrame("Nivel1/Fantasmas/Celeste/arriba1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Celeste/arriba2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Celeste/arriba3.png");
    }
}
