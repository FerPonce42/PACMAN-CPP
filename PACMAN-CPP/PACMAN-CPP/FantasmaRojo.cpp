#include "FantasmaRojo.h"
#include <iostream>
#include <cmath>

// Constructor de la clase FantasmaRojo que inicializa la textura, el sprite y la velocidad del fantasma
FantasmaRojo::FantasmaRojo(const std::string& rutaTextura, float posX, float posY, float velocidad)
    : velocidad(velocidad) {
    if (!textura.loadFromFile("Nivel1/fantasmarojo.png")) {
        std::cerr << "Error al cargar la textura del fantasma." << std::endl;
    }
    sprite.setTexture(textura);
    sprite.setPosition(740, 500);
}

// M�todo para dibujar al fantasma en la ventana
void FantasmaRojo::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(sprite);
}

void FantasmaRojo::mover(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio, sf::Vector2f posJugador) {
    sf::Vector2f posicionActual = sprite.getPosition();

    // Calcular la dirección hacia el jugador
    sf::Vector2f direccionJugador = posJugador - posicionActual;
    float distancia = std::sqrt(direccionJugador.x * direccionJugador.x + direccionJugador.y * direccionJugador.y);
    if (distancia != 0) {
        direccion = direccionJugador / distancia; // Normalizar la dirección
    }
    else {
        direccion = sf::Vector2f(0, 0);
    }

    // Calcular la nueva posición del fantasma
    sf::Vector2f nuevaPosicion = posicionActual + direccion * velocidad;

    // Verificar si la nueva posición es válida en el mapa
    if (posicionValida(nuevaPosicion, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
        sprite.setPosition(nuevaPosicion);
    }
}


// M�todo para obtener la posici�n actual del fantasma
sf::Vector2f FantasmaRojo::getPosicion() const {
    return sprite.getPosition();
}

// M�todo para determinar si una posici�n es v�lida en el mapa
bool FantasmaRojo::posicionValida(sf::Vector2f posicion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
    int fila = static_cast<int>((posicion.y - posYInicio) / altoCelda);
    int columna = static_cast<int>((posicion.x - posXInicio) / anchoCelda);

    if (fila >= 0 && fila < altoMapa && columna >= 0 && columna < anchoMapa) {
        return mapa[fila][columna] == 0;
    }
    return false;
}