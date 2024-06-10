#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Poderes {
public:
    Poderes(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);

    void dibujar(sf::RenderWindow& ventana);
    bool verificarColision(sf::Sprite& sprite);
    void activarPoder();
    bool estaActivo() const;

private:
    std::vector<sf::CircleShape> poderes;
    float radioPoder;
    bool poderActivo;
    sf::Clock relojPoder; 
};
