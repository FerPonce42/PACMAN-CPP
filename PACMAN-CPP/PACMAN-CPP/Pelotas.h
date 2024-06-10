#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Pelotas {
public:
    Pelotas(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);

    void dibujar(sf::RenderWindow& ventana);
    bool verificarColision(sf::Sprite& sprite);
    int getCantidadPelotas(); 

private:
    std::vector<sf::CircleShape> bolitas;
    float radioBolita;
};