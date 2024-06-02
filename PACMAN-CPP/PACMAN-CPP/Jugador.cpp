#include "Jugador.h"
#include <iostream>

Jugador::Jugador(float x, float y, float velocidad)
    : velocidad(velocidad), direccion(0, 0) {
    animacion = new Animacion(0.1f);  // Tiempo entre frames
    animacion->agregarFrame("Nivel1/derecha1.png");
    animacion->agregarFrame("Nivel1/derecha2.png");
    animacion->agregarFrame("Nivel1/derecha3.png");

    sprite.setPosition(x, y);
    sprite.setScale(0.8f, 0.8f);
}

bool Jugador::posicionValida(sf::Vector2f nuevaPosicion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
    float jugadorAncho = sprite.getGlobalBounds().width;
    float jugadorAlto = sprite.getGlobalBounds().height;
    std::vector<sf::Vector2f> puntos;

    puntos.push_back(nuevaPosicion);
    puntos.push_back({ nuevaPosicion.x + jugadorAncho, nuevaPosicion.y });
    puntos.push_back({ nuevaPosicion.x, nuevaPosicion.y + jugadorAlto });
    puntos.push_back({ nuevaPosicion.x + jugadorAncho, nuevaPosicion.y + jugadorAlto });

    for (float x = nuevaPosicion.x + 1; x < nuevaPosicion.x + jugadorAncho; x += anchoCelda / 2) {
        puntos.push_back({ x, nuevaPosicion.y });
        puntos.push_back({ x, nuevaPosicion.y + jugadorAlto });
    }
    for (float y = nuevaPosicion.y + 1; y < nuevaPosicion.y + jugadorAlto; y += altoCelda / 2) {
        puntos.push_back({ nuevaPosicion.x, y });
        puntos.push_back({ nuevaPosicion.x + jugadorAncho, y });
    }

    for (auto& punto : puntos) {
        int columna = static_cast<int>((punto.x - posXInicio) / anchoCelda);
        int fila = static_cast<int>((punto.y - posYInicio) / altoCelda);

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
    animacion->aplicarA(sprite);
    ventana.draw(sprite);
}

void Jugador::setDireccion(sf::Vector2f nuevaDireccion) {
    direccion = nuevaDireccion;
    // Cambiar animaciones basadas en la dirección
    delete animacion;
    animacion = new Animacion(0.1f);  // Tiempo entre frames

    if (direccion.x > 0) {
        animacion->agregarFrame("Nivel1/derecha1.png");
        animacion->agregarFrame("Nivel1/derecha2.png");
        animacion->agregarFrame("Nivel1/derecha3.png");
    }
    else if (direccion.x < 0) {
        animacion->agregarFrame("Nivel1/izquierda1.png");
        animacion->agregarFrame("Nivel1/izquierda2.png");
        animacion->agregarFrame("Nivel1/izquierda3.png");
    }
    else if (direccion.y > 0) {
        animacion->agregarFrame("Nivel1/abajo1.png");
        animacion->agregarFrame("Nivel1/abajo2.png");
        animacion->agregarFrame("Nivel1/abajo3.png");
    }
    else if (direccion.y < 0) {
        animacion->agregarFrame("Nivel1/arriba1.png");
        animacion->agregarFrame("Nivel1/arriba2.png");
        animacion->agregarFrame("Nivel1/arriba3.png");
    }
}

sf::Vector2f Jugador::getPosicion() const {
    return sprite.getPosition();
}

sf::Vector2f Jugador::getDireccion() const {
    return direccion;
}

void Jugador::actualizarAnimacion(float deltaTime) {
    animacion->actualizar(deltaTime);
}