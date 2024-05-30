#pragma once

#include <SFML/Graphics.hpp>
#include "Jugador.h"
#include "Musica.h"
#include "FantasmaRojo.h"

class Nivel1 {
public:
    // Constructor de la clase Nivel1 que recibe una referencia a la ventana SFML, el ancho y el alto de la ventana
    Nivel1(sf::RenderWindow& ventana, float ancho, float alto);

    // M�todo para mostrar el nivel en la ventana
    void mostrar();

    // M�todo para actualizar la l�gica del nivel
    void actualizar();

    // M�todo para manejar eventos de la ventana
    void manejarEventos();

    // M�todo para verificar si una posici�n dada es v�lida en el nivel
    bool posicionValida(sf::Vector2f posicion);


private:
    sf::RenderWindow& ventana; // Referencia a la ventana SFML
    Musica musicaNivel1; // Objeto de la clase Musica para reproducir m�sica en el nivel
    sf::Texture fondoTextura; // Textura para el fondo del nivel
    sf::Sprite fondoSprite; // Sprite para el fondo del nivel
    Jugador jugador; // Objeto de la clase Jugador para representar al jugador en el nivel
    FantasmaRojo fantasmaRojo; // Objeto de la clase FantasmaRojo para representar al fantasma en el nivel
    std::vector<sf::Sprite> objetos; // Vector de sprites para otros objetos en el nivel
    const int anchoMapa = 30; // Ancho del mapa del nivel
    const int altoMapa = 12; // Alto del mapa del nivel
    int** mapa; // Mapa del nivel representado como una matriz de enteros
    float anchoCelda; // Ancho de cada celda en el mapa
    float altoCelda; // Alto de cada celda en el mapa
    float posXInicio; // Posici�n inicial en el eje X del jugador
    float posYInicio; // Posici�n inicial en el eje Y del jugador

    // M�todo privado para inicializar el mapa del nivel
    void inicializarMapa();
};