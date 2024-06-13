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
    // Manejo de cambio de comportamiento cuando se activa/desactiva el poder
    if (powerActive && !poderActivo) {
        poderActivo = true;
        cambiarTexturaPorPoder();
        direccionActual = -direccionActual; // Cambiar dirección opuesta
    }
    else if (!powerActive && poderActivo) {
        poderActivo = false;
        animacion->limpiarFrames();
        animacion->agregarFrame("Nivel1/Fantasmas/Celeste/derecha1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Celeste/derecha2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Celeste/derecha3.png");
        direccionActual = -direccionActual; // Cambiar dirección opuesta
    }

    // Obtener la posición actual del fantasma
    sf::Vector2f posicionActual = sprite.getPosition();

    // Lista de posibles direcciones a considerar
    std::vector<sf::Vector2f> posiblesDirecciones = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    // Determinar si Pacman está cerca
    bool enRango = std::hypot(posicionActual.x - playerPosition.x, posicionActual.y - playerPosition.y) < 150;

    if (enRango && !powerActive) {
        // Calcular la distancia euclidiana al jugador
        float mejorDistancia = std::numeric_limits<float>::max();
        sf::Vector2f mejorDireccion = direccionActual;

        for (const auto& dir : posiblesDirecciones) {
            sf::Vector2f nuevaPosicion = posicionActual + dir * velocidad;
            if (posicionValida(nuevaPosicion, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
                float nuevaDistancia = std::hypot(nuevaPosicion.x - playerPosition.x, nuevaPosicion.y - playerPosition.y);
                if (nuevaDistancia < mejorDistancia) {
                    mejorDistancia = nuevaDistancia;
                    mejorDireccion = dir;
                }
            }
        }
        direccionActual = mejorDireccion;
    }
    else {
        // Verificar si la dirección actual sigue siendo válida
        sf::Vector2f nuevaPosicion = posicionActual + direccionActual * velocidad;
        if (!posicionValida(nuevaPosicion, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
            // Elegir una nueva dirección aleatoria válida
            std::vector<sf::Vector2f> direccionesValidas;

            for (const auto& dir : posiblesDirecciones) {
                nuevaPosicion = posicionActual + dir * velocidad;
                if (posicionValida(nuevaPosicion, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
                    direccionesValidas.push_back(dir);
                }
            }

            // Si hay direcciones válidas, elegir una aleatoriamente
            if (!direccionesValidas.empty()) {
                int indiceAleatorio = rand() % direccionesValidas.size();
                direccionActual = direccionesValidas[indiceAleatorio];
            }
        }
    }

    // Mover el fantasma en la dirección seleccionada
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