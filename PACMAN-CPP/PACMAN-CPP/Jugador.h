#pragma once 
#include <SFML/Graphics.hpp> 

class Jugador {
public:
    // Constructor de la clase Jugador
    Jugador(float x, float y, float velocidad);

    // M�todo para mover al jugador en una direcci�n dada
    void mover(sf::Vector2f direccion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);

    // M�todo para dibujar al jugador en una ventana dada
    void dibujar(sf::RenderWindow& ventana);

    // M�todo para cambiar la textura del jugador
    void cambiarTextura(const std::string& archivoTextura);

    // M�todo para establecer la direcci�n del jugador
    void setDireccion(sf::Vector2f nuevaDireccion);

    // M�todo para obtener la posici�n del jugador
    sf::Vector2f getPosicion() const;

    // M�todo para obtener la direcci�n del jugador
    sf::Vector2f getDireccion() const;

private:
    sf::Texture textura; // Textura del jugador
    sf::Sprite sprite; // Sprite del jugador
    float velocidad; // Velocidad de movimiento del jugador
    sf::Vector2f direccion; // Direcci�n de movimiento del jugador

    // M�todo privado para verificar si la posici�n propuesta es v�lida en el mapa
    bool posicionValida(sf::Vector2f nuevaPosicion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);
};