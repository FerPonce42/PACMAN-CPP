#include "FantasmaPadre.h"

FantasmaPadre::FantasmaPadre(const std::string& textureFile, float startX, float startY, float speed)
    : position(startX, startY), speed(speed) {
    if (!texture.loadFromFile(textureFile)) {
        // Handle loading error
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
}

void FantasmaPadre::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Vector2f FantasmaPadre::getPosition() const {
    return position;
}
