#pragma once

#include <SFML/Graphics.hpp>
#include "Jugador1.h"
#include "Jugador2.h"
#include "Musica.h"
#include "Ganador.h"
#include "Pelotas.h"

class Nivel3 {
public:
    Nivel3(sf::RenderWindow& ventana, float ancho, float alto);
    ~Nivel3();  // Destructor para liberar memoria
    void mostrar();
    void actualizar();
    void manejarEventos();
    bool posicionValida(sf::Vector2f posicion);
    void verificarColisiones();

private:
    sf::RenderWindow& ventana;
    Musica musicaNivel3;
    sf::Texture fondoTextura;
    sf::Sprite fondoSprite;
    Jugador1 jugador1;
    Jugador2 jugador2;
    Pelotas* pelotas;  // Cambiado a puntero
    std::vector<sf::Sprite> objetos;
    const int anchoMapa = 30;
    const int altoMapa = 12;
    int** mapa;
    float anchoCelda;
    float altoCelda;
    float posXInicio;
    float posYInicio;

    void inicializarMapa();
};
