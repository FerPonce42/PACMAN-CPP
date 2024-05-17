#pragma once 
#include <SFML/Graphics.hpp> 

class Jugador {
public:
    // Constructor de la clase Jugador
    Jugador(float x, float y, float velocidad);

    // Método para mover al jugador en una dirección dada
    void mover(sf::Vector2f direccion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);

    // Método para dibujar al jugador en una ventana dada
    void dibujar(sf::RenderWindow& ventana);

    // Método para cambiar la textura del jugador
    void cambiarTextura(const std::string& archivoTextura);

    // Método para establecer la dirección del jugador
    void setDireccion(sf::Vector2f nuevaDireccion);

    // Método para obtener la posición del jugador
    sf::Vector2f getPosicion() const;

    // Método para obtener la dirección del jugador
    sf::Vector2f getDireccion() const;

private:
    sf::Texture textura; // Textura del jugador
    sf::Sprite sprite; // Sprite del jugador
    float velocidad; // Velocidad de movimiento del jugador
    sf::Vector2f direccion; // Dirección de movimiento del jugador

    // Método privado para verificar si la posición propuesta es válida en el mapa
    bool posicionValida(sf::Vector2f nuevaPosicion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);
};
