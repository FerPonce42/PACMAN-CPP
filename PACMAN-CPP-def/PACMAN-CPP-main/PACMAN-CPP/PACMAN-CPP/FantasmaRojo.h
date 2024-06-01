#pragma once

#include <SFML/Graphics.hpp>

class FantasmaRojo {
public:
    // Constructor de la clase FantasmaRojo que recibe la ruta de la textura, la posici�n inicial y la velocidad
    FantasmaRojo(const std::string& rutaTextura, float posX, float posY, float velocidad);

    // M�todo para dibujar al fantasma en la ventana
    void dibujar(sf::RenderWindow& ventana);

    // M�todo para mover al fantasma basado en el mapa, la posici�n del jugador y otros par�metros
    void mover(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio, sf::Vector2f posJugador);

    // M�todo para obtener la posici�n actual del fantasma
    sf::Vector2f getPosicion() const;

private:
    sf::Texture textura; // Textura del fantasma
    sf::Sprite sprite; // Sprite del fantasma
    float velocidad; // Velocidad del fantasma
    sf::Vector2f direccion; // Direcci�n actual del fantasma

    // M�todo para determinar si una posici�n es v�lida en el mapa
    bool posicionValida(sf::Vector2f posicion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);
};