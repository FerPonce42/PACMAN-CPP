#include "Pelotas.h"
#include <iostream>

Pelotas::Pelotas(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
    radioBolita = std::min(anchoCelda, altoCelda) / 8;

    for (int i = 0; i < altoMapa; ++i) {
        for (int j = 0; j < anchoMapa; ++j) {
            if (mapa[i][j] == 0) {
                sf::CircleShape bolita(radioBolita);
                bolita.setFillColor(sf::Color::White);
                bolita.setPosition(posXInicio + j * anchoCelda + anchoCelda / 2 - radioBolita, posYInicio + i * altoCelda + altoCelda / 2 - radioBolita);
                bolitas.push_back(bolita);

            }
        }
    }
}

void Pelotas::dibujar(sf::RenderWindow& ventana) {
    for (auto& bolita : bolitas) {
        ventana.draw(bolita);
    }
}

bool Pelotas::verificarColision(sf::Sprite& sprite) {
    for (auto it = bolitas.begin(); it != bolitas.end(); ++it) {
        if (sprite.getGlobalBounds().intersects(it->getGlobalBounds())) {
            bolitas.erase(it);
            return true;
        }
    }
    return false;
}

int Pelotas::getCantidadPelotas() {
    return bolitas.size(); 
}