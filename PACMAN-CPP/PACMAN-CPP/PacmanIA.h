#pragma once
#include <SFML/Graphics.hpp>
#include "Animacion.h"
#include "Ganador.h"

class PacmanIA {
public:
    PacmanIA(float x, float y, float velocidad);

    void mover(sf::Vector2f direccion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);
    void moverAI(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio, sf::Vector2f ghostPosition, bool powerActive); // Nuevo
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
    void aumentarPuntaje(int puntos);
    int getPuntaje() const;
    void dibujarPuntaje(sf::RenderWindow& ventana);
    void activarPoder(bool activado); // Nuevo

private:
    sf::Sprite sprite;
    float velocidad;
    sf::Vector2f direccion;
    sf::Vector2f direccionActual; // Nueva variable
    Animacion* animacion;
    int vidas;
    sf::Vector2f posicionInicial;
    int puntaje;
    bool poderActivo; // Nueva variable

    bool posicionValida(sf::Vector2f nuevaPosicion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);

    // Métodos y variables adicionales para la IA
    void moveRandomly(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);
    void avoidGhost(sf::Vector2f ghostPosition, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);
    void chaseGhost(sf::Vector2f ghostPosition, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);
    void seleccionarNuevaDireccion(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio); // Nuevo método
};
