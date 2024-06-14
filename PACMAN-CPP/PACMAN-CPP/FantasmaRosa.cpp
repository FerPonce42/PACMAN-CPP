#include "FantasmaRosa.h"

FantasmaRosa::FantasmaRosa(float x, float y, float velocidad)
    : FantasmaRojo(x, y, 1) {
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
    // Manejo de cambio de comportamiento cuando se activa/desactiva el poder
    if (powerActive && !poderActivo) {
        poderActivo = true;
        cambiarTexturaPorPoder();
        direccionActual = -direccionActual; // Cambiar dirección opuesta
    }
    else if (!powerActive && poderActivo) {
        poderActivo = false;
        animacion->limpiarFrames();
        animacion->agregarFrame("Nivel1/Fantasmas/Rosa/derecha1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rosa/derecha2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rosa/derecha3.png");
        direccionActual = -direccionActual; // Cambiar dirección opuesta
    }

    // Obtener la posición actual del fantasma
    sf::Vector2f posicionActual = sprite.getPosition();

    // Lista de posibles direcciones a considerar
    std::vector<sf::Vector2f> posiblesDirecciones = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    // Calcular la posición futura predicha de Pac-Man
    sf::Vector2f playerDirection = playerPosition - posicionActual;
    if (std::hypot(playerDirection.x, playerDirection.y) > 0) {
        playerDirection /= std::hypot(playerDirection.x, playerDirection.y); // Normalizar la dirección
    }
    sf::Vector2f posicionPredecida = playerPosition + playerDirection * 4.0f; // Ajusta este valor según sea necesario

    // Determinar si Pac-Man está en rango
    bool enRango = std::hypot(posicionActual.x - playerPosition.x, posicionActual.y - playerPosition.y) < 150;

    if (enRango && !powerActive) {
        // Calcular la distancia euclidiana a la posición predicha
        float mejorDistancia = std::numeric_limits<float>::max();
        sf::Vector2f mejorDireccion = direccionActual;

        for (const auto& dir : posiblesDirecciones) {
            sf::Vector2f nuevaPosicion = posicionActual + dir * velocidad;
            if (posicionValida(nuevaPosicion, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
                float nuevaDistancia = std::hypot(nuevaPosicion.x - posicionPredecida.x, nuevaPosicion.y - posicionPredecida.y);
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
