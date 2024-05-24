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
    sprite.setScale(0.8f, 0.8f); // Escala el tamaño del fantasma
}

// Método para dibujar al fantasma en la ventana
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

// Método para obtener la posición actual del fantasma
sf::Vector2f FantasmaRojo::getPosicion() const {
    return sprite.getPosition();
}

// Método para determinar si una posición es válida en el mapa
bool FantasmaRojo::posicionValida(sf::Vector2f posicion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
    float fantasmaAncho = sprite.getGlobalBounds().width; // Ancho del sprite del fantasma
    float fantasmaAlto = sprite.getGlobalBounds().height; // Alto del sprite del fantasma

    std::vector<sf::Vector2f> puntos; // Vector para almacenar puntos de colisión

    // Esquinas del fantasma
    puntos.push_back(posicion);
    puntos.push_back({ posicion.x + fantasmaAncho, posicion.y });
    puntos.push_back({ posicion.x, posicion.y + fantasmaAlto });
    puntos.push_back({ posicion.x + fantasmaAncho, posicion.y + fantasmaAlto });

    // Puntos intermedios en los lados del fantasma
    for (float x = posicion.x + 1; x < posicion.x + fantasmaAncho; x += anchoCelda / 2) {
        puntos.push_back({ x, posicion.y });
        puntos.push_back({ x, posicion.y + fantasmaAlto });
    }
    for (float y = posicion.y + 1; y < posicion.y + fantasmaAlto; y += altoCelda / 2) {
        puntos.push_back({ posicion.x, y });
        puntos.push_back({ posicion.x + fantasmaAncho, y });
    }

    // Verificar cada punto en el mapa
    for (auto& punto : puntos) {
        int columna = static_cast<int>((punto.x - posXInicio) / anchoCelda); // Columna en el mapa
        int fila = static_cast<int>((punto.y - posYInicio) / altoCelda); // Fila en el mapa

        // Verifica si el punto está fuera de los límites del mapa o colisiona con un obstáculo
        if (fila < 0 || fila >= altoMapa || columna < 0 || columna >= anchoMapa || mapa[fila][columna] != 0) {
            return false; // La posición no es válida
        }
    }

    return true; // La posición es válida
}
