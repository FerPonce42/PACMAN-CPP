#include "FantasmaNaranja.h"

FantasmaNaranja::FantasmaNaranja(float x, float y, float velocidad)
    : FantasmaRojo(x, y, velocidad) {
    animacion->limpiarFrames();
    animacion->agregarFrame("Nivel1/Fantasmas/Naranja/derecha1.png");
    animacion->agregarFrame("Nivel1/Fantasmas/Naranja/derecha2.png");
    animacion->agregarFrame("Nivel1/Fantasmas/Naranja/derecha3.png");

    sprite.setPosition(715, 480); // FANTASMA CELESTE
    sprite.setScale(0.8f, 0.8f);
}

void FantasmaNaranja::setPosicionInicial() {
    sprite.setPosition(715, 480);
}

void FantasmaNaranja::moverAI(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio, sf::Vector2f playerPosition, bool powerActive) {
    if (powerActive && !poderActivo) {
        poderActivo = true;
        cambiarTexturaPorPoder();
    }
    else if (!powerActive && poderActivo) {
        poderActivo = false;
        animacion->limpiarFrames();
        animacion->agregarFrame("Nivel1/Fantasmas/Naranja/derecha1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Naranja/derecha2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Naranja/derecha3.png");
    }

    if (poderActivo) {
        avoidPlayer(playerPosition, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
    }
    else {
        chasePlayer(playerPosition, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
    }

    mover(direccionActual, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
}

void FantasmaNaranja::setDireccion(sf::Vector2f nuevaDireccion) {
    direccion = nuevaDireccion;

    animacion->limpiarFrames();

    if (direccion.x > 0) {
        animacion->agregarFrame("Nivel1/Fantasmas/Naranja/derecha1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Naranja/derecha2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Naranja/derecha3.png");
    }
    else if (direccion.x < 0) {
        animacion->agregarFrame("Nivel1/Fantasmas/Naranja/izquierda1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Naranja/izquierda2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Naranja/izquierda3.png");
    }
    else if (direccion.y > 0) {
        animacion->agregarFrame("Nivel1/Fantasmas/Naranja/abajo1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Naranja/abajo2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Naranja/abajo3.png");
    }
    else if (direccion.y < 0) {
        animacion->agregarFrame("Nivel1/Fantasmas/Naranja/arriba1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Naranja/arriba2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Naranja/arriba3.png");
    }
}
