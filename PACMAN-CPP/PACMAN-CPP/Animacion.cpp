#include "Animacion.h"
#include <iostream>

Animacion::Animacion(float frameTime, bool loop)
    : frameTime(frameTime), loop(loop), currentTime(0), currentFrame(0) {}

void Animacion::agregarFrame(const std::string& archivoTextura) {
    sf::Texture textura;
    if (!textura.loadFromFile(archivoTextura)) {
        std::cerr << "Error al cargar la textura: " << archivoTextura << std::endl;
    }
    else {
        texturas.push_back(textura);
    }
}

void Animacion::limpiarFrames() {
    texturas.clear(); // Limpiar frames existentes
}

void Animacion::actualizar(float deltaTime) {
    if (texturas.empty()) return;

    currentTime += deltaTime;
    if (currentTime >= frameTime) {
        currentTime = 0;
        currentFrame++;
        if (currentFrame >= texturas.size()) {
            if (loop) {
                currentFrame = 0;
            }
            else {
                currentFrame = texturas.size() - 1;
            }
        }
    }
}

void Animacion::aplicarA(sf::Sprite& sprite) {
    if (!texturas.empty()) {
        sprite.setTexture(texturas[currentFrame]);
    }
}