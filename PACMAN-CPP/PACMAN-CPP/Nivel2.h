#pragma once
#ifndef NIVEL2_H
#define NIVEL2_H

#include <SFML/Graphics.hpp>
#include "Musica.h" 

class Nivel2 {
public:
    Nivel2(sf::RenderWindow& ventana, float ancho, float alto);

    void mostrar();
    void actualizar();
    void manejarEventos();

private:
    sf::RenderWindow& ventana;
    Musica musicaNivel2; 
    sf::Texture fondoTextura;
    sf::Sprite fondoSprite;
    
};

#endif