#pragma once
#include <SFML/Graphics.hpp>
#include "Pathfinding.h"

class FantasmaRojo {
public:
    FantasmaRojo(const std::string& rutaTextura, float posX, float posY, float velocidad);
    void dibujar(sf::RenderWindow& ventana);
    void mover(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio, sf::Vector2f posJugador);
    sf::Vector2f getPosicion() const;

private:
    sf::Texture textura;
    sf::Sprite sprite;
    float velocidad;
    sf::Vector2f direccion;
    std::vector<sf::Vector2f> camino;
    size_t indiceCamino;
    Pathfinding* pathfinding;

    bool posicionValida(sf::Vector2f posicion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);
    void actualizarCamino(sf::Vector2f posJugador);
};
