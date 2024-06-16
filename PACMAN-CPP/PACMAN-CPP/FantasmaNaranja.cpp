#include "FantasmaNaranja.h"

FantasmaNaranja::FantasmaNaranja(float x, float y, float velocidad)
    : FantasmaRojo(x, y, 1) {
    animacion->limpiarFrames();
    animacion->agregarFrame("Nivel1/Fantasmas/Naranja/derecha1.png");
    animacion->agregarFrame("Nivel1/Fantasmas/Naranja/derecha2.png");
    animacion->agregarFrame("Nivel1/Fantasmas/Naranja/derecha3.png");

    sprite.setPosition(715, 480); 
    sprite.setScale(0.8f, 0.8f);
}

void FantasmaNaranja::setPosicionInicial() {
    sprite.setPosition(715, 480);
}

void FantasmaNaranja::moverAI(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio, sf::Vector2f playerPosition, bool powerActive) {
    
    if (powerActive && !poderActivo) {
        poderActivo = true;
        cambiarTexturaPorPoder();
        direccionActual = -direccionActual; 
    }
    else if (!powerActive && poderActivo) {
        poderActivo = false;
        animacion->limpiarFrames();
        animacion->agregarFrame("Nivel1/Fantasmas/Naranja/derecha1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Naranja/derecha2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Naranja/derecha3.png");
        direccionActual = -direccionActual; 
    }

   
    sf::Vector2f posicionActual = sprite.getPosition();

    
    std::vector<sf::Vector2f> posiblesDirecciones = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    
    bool enRango = std::hypot(posicionActual.x - playerPosition.x, posicionActual.y - playerPosition.y) < 50;

    if (enRango && !powerActive) {
      
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
        
        sf::Vector2f nuevaPosicion = posicionActual + direccionActual * velocidad;
        if (!posicionValida(nuevaPosicion, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
           
            std::vector<sf::Vector2f> direccionesValidas;

            for (const auto& dir : posiblesDirecciones) {
                nuevaPosicion = posicionActual + dir * velocidad;
                if (posicionValida(nuevaPosicion, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
                    direccionesValidas.push_back(dir);
                }
            }

          
            if (!direccionesValidas.empty()) {
                int indiceAleatorio = rand() % direccionesValidas.size();
                direccionActual = direccionesValidas[indiceAleatorio];
            }
        }
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
