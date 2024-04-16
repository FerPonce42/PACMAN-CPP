#pragma once
#include <SFML/Graphics.hpp>
#include "Jugador.h"
#include "Musica.h"

class Nivel1 {
public:
    Nivel1(sf::RenderWindow& ventana, float ancho, float alto);

    void mostrar();
    void actualizar();
    void manejarEventos();

private:
    sf::RenderWindow& ventana;
    Musica musicaNivel1;
    sf::Texture fondoTextura;
    sf::Sprite fondoSprite;
    Jugador jugador;
};