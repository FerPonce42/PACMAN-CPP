#include "Poderes.h"
#include <iostream>

Poderes::Poderes(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio)
    : poderActivo(false) {
    radioPoder = std::min(anchoCelda, altoCelda) / 5;

    for (int i = 0; i < altoMapa; ++i) {
        for (int j = 0; j < anchoMapa; ++j) {
            if (mapa[i][j] == 3) {  // Dibujar pelotas celestes en los 3 del mapa
                sf::CircleShape poder(radioPoder);
                poder.setFillColor(sf::Color::Cyan);
                poder.setPosition(posXInicio + j * anchoCelda + anchoCelda / 2 - radioPoder, posYInicio + i * altoCelda + altoCelda / 2 - radioPoder);
                poderes.push_back(poder);
            }
        }
    }
}

void Poderes::dibujar(sf::RenderWindow& ventana) {
    for (auto& poder : poderes) {
        ventana.draw(poder);
    }
}

bool Poderes::verificarColision(sf::Sprite& sprite) {
    for (auto it = poderes.begin(); it != poderes.end(); ++it) {
        if (sprite.getGlobalBounds().intersects(it->getGlobalBounds())) {
            poderes.erase(it);
            activarPoder();
            return true;
        }
    }
    return false;
}

void Poderes::activarPoder() {
    poderActivo = true;
    relojPoder.restart(); // Reinicia el reloj
}

bool Poderes::estaActivo() const {
    return poderActivo && relojPoder.getElapsedTime().asSeconds() <= 5;
}
