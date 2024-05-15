#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Jugador {
public:
    Jugador(float x, float y, float velocidad);

    void mover(sf::Vector2f direccion, const std::vector<sf::Sprite>& objetos);
    void dibujar(sf::RenderWindow& ventana);
    void cambiarTextura(const std::string& archivoTextura);
    void setDireccion(sf::Vector2f nuevaDireccion);
    sf::Vector2f getPosicion() const;

private:
    sf::Texture textura;
    sf::Sprite sprite;
    float velocidad;
    sf::Vector2f direccion;
};
