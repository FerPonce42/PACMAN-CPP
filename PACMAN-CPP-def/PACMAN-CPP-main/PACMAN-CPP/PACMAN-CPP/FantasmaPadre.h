#pragma once
#include <SFML/Graphics.hpp>

class FantasmaPadre {
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;
    float speed;

public:
    FantasmaPadre(const std::string& textureFile, float startX, float startY, float speed);
    virtual ~FantasmaPadre() {}

    virtual void move(const sf::Vector2f& target, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) = 0;
    void draw(sf::RenderWindow& window);
    sf::Vector2f getPosition() const;
};


