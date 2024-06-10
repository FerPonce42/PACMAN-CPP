#pragma once
#include <SFML/Graphics.hpp>
#include "Animacion.h"
#include "Ganador.h"

class FantasmaJugador {
public:
    FantasmaJugador(float x, float y, float velocidad);

    void mover(sf::Vector2f direccion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);
    void dibujar(sf::RenderWindow& ventana);
    void setDireccion(sf::Vector2f nuevaDireccion);
    sf::Vector2f getPosicion() const;
    sf::Vector2f getDireccion() const;
    void actualizarAnimacion(float deltaTime);
    int getVidas() const;
    void dibujarVidas(sf::RenderWindow& ventana);
    void reducirVida();
    void setPosicionInicial();
    sf::Sprite& getSprite();
    void mostrarVentanaGanador(sf::RenderWindow& mainWindow, int ganador);
    void cambiarTexturaPorPoder();

private:
    sf::Sprite sprite;
    float velocidad;
    sf::Vector2f direccion;
    Animacion* animacion;
    int vidas;
    sf::Vector2f posicionInicial;

    bool posicionValida(sf::Vector2f nuevaPosicion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);
};