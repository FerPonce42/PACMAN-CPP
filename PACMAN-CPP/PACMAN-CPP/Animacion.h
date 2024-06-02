#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Animacion {
public:
    Animacion(float frameTime, bool loop = true);

    void agregarFrame(const std::string& archivoTextura);
    void actualizar(float deltaTime);
    void aplicarA(sf::Sprite& sprite);

private:
    std::vector<sf::Texture> texturas;
    float frameTime;
    float currentTime;
    bool loop;
    int currentFrame;
};
