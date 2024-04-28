#pragma once
#include <SFML/Graphics.hpp>

class FantasmaPadre {
public:
    FantasmaPadre(float x, float y, float velocidad);
    virtual ~FantasmaPadre();

    virtual void mover(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio, sf::Vector2f posicionJugador) = 0;
    void dibujar(sf::RenderWindow& ventana);
    void cambiarTextura(const std::string& archivoTextura);
    void setDireccion(sf::Vector2f nuevaDireccion);

    // Método para obtener la posición del fantasma
    sf::Vector2f getPosicion() const;

protected:
    sf::Texture textura;
    sf::Sprite sprite;
    float velocidad;
    sf::Vector2f direccion;
};
