#pragma once

#include <SFML/Graphics.hpp>

class FantasmaRojo {
public:
    // Constructor de la clase FantasmaRojo que recibe la ruta de la textura, la posición inicial y la velocidad
    FantasmaRojo(const std::string& rutaTextura, float posX, float posY, float velocidad);

    // Método para dibujar al fantasma en la ventana
    void dibujar(sf::RenderWindow& ventana);

    // Método para mover al fantasma basado en el mapa, la posición del jugador y otros parámetros
    void mover(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio, sf::Vector2f posJugador);

    // Método para obtener la posición actual del fantasma
    sf::Vector2f getPosicion() const;

private:
    sf::Texture textura; // Textura del fantasma
    sf::Sprite sprite; // Sprite del fantasma
    float velocidad; // Velocidad del fantasma
    sf::Vector2f direccion; // Dirección actual del fantasma

    // Método para determinar si una posición es válida en el mapa
    bool posicionValida(sf::Vector2f posicion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);
};
