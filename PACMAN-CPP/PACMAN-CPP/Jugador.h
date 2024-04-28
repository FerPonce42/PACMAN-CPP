#pragma once
#include <SFML/Graphics.hpp>

class Jugador {
public:
    Jugador(float x, float y, float velocidad);

    void mover(sf::Vector2f direccion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);
    void dibujar(sf::RenderWindow& ventana);
    void cambiarTextura(const std::string& archivoTextura);
    void setDireccion(sf::Vector2f nuevaDireccion); // Método para establecer la dirección del jugador

    // Método para obtener la posición del jugador
    sf::Vector2f getPosicion() const;

private:
    sf::Texture textura;
    sf::Sprite sprite;
    float velocidad;
    sf::Vector2f direccion;
};
