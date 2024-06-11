#pragma once
#include <SFML/Graphics.hpp>
#include "Animacion.h"
#include "Ganador.h"

class FantasmaRojo {
public:
    FantasmaRojo(float x, float y, float velocidad);

    virtual void mover(sf::Vector2f direccion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);
    virtual void moverAI(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio, sf::Vector2f playerPosition, bool powerActive);
    virtual void dibujar(sf::RenderWindow& ventana);
    virtual void setDireccion(sf::Vector2f nuevaDireccion);
    sf::Vector2f getPosicion() const;
    sf::Vector2f getDireccion() const;
    virtual void actualizarAnimacion(float deltaTime);
    int getVidas() const;
    void dibujarVidas(sf::RenderWindow& ventana);
    void reducirVida();
    virtual void setPosicionInicial();
    sf::Sprite& getSprite();
    void mostrarVentanaGanador(sf::RenderWindow& mainWindow, int ganador);
    void cambiarTexturaPorPoder();

protected:
    sf::Sprite sprite;
    float velocidad;
    sf::Vector2f direccion;
    sf::Vector2f direccionActual;
    Animacion* animacion;
    int vidas;
    sf::Vector2f posicionInicial;
    bool poderActivo;

    bool posicionValida(sf::Vector2f nuevaPosicion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);

    void avoidPlayer(sf::Vector2f playerPosition, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);
    void chasePlayer(sf::Vector2f playerPosition, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);
    void seleccionarNuevaDireccion(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);
};
