#pragma once 

#include <SFML/Graphics.hpp> 
#include "Jugador.h" 
#include "Musica.h" 

class Nivel1 {
public:
    // Constructor de la clase Nivel1 que recibe una referencia a la ventana SFML, el ancho y el alto de la ventana
    Nivel1(sf::RenderWindow& ventana, float ancho, float alto);

    // Método para mostrar el nivel en la ventana
    void mostrar();

    // Método para actualizar la lógica del nivel
    void actualizar();

    // Método para manejar eventos de la ventana
    void manejarEventos();

    // Método para verificar si una posición dada es válida en el nivel
    bool posicionValida(sf::Vector2f posicion);

private:
    sf::RenderWindow& ventana; // Referencia a la ventana SFML
    Musica musicaNivel1; // Objeto de la clase Musica para reproducir música en el nivel
    sf::Texture fondoTextura; // Textura para el fondo del nivel
    sf::Sprite fondoSprite; // Sprite para el fondo del nivel
    Jugador jugador; // Objeto de la clase Jugador para representar al jugador en el nivel
    std::vector<sf::Sprite> objetos; // Vector de sprites para otros objetos en el nivel
    const int anchoMapa = 30; // Ancho del mapa del nivel
    const int altoMapa = 12; // Alto del mapa del nivel
    int** mapa; // Mapa del nivel representado como una matriz de enteros
    float anchoCelda; // Ancho de cada celda en el mapa
    float altoCelda; // Alto de cada celda en el mapa
    float posXInicio; // Posición inicial en el eje X del jugador
    float posYInicio; // Posición inicial en el eje Y del jugador

    // Método privado para inicializar el mapa del nivel
    void inicializarMapa();
};
