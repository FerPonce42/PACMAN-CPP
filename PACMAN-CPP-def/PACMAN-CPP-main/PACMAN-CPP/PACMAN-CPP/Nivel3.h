#pragma once
#ifndef NIVEL3_H
#define NIVEL3_H

#include <SFML/Graphics.hpp>
#include "Musica.h" 

class Nivel3 {
public:
    Nivel3(sf::RenderWindow& ventana, float ancho, float alto);

    void mostrar();
    void actualizar();
    void manejarEventos();

private:
    sf::RenderWindow& ventana;
    Musica musicaNivel3; 
    sf::Texture fondoTextura;
    sf::Sprite fondoSprite;
    
};

#endif 
