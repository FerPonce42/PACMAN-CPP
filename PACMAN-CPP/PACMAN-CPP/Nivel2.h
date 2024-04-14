#pragma once
#ifndef NIVEL2_H
#define NIVEL2_H

#include <SFML/Graphics.hpp>
#include "Musica.h" // Agregamos la inclusión de Musica.h

class Nivel2 {
public:
    Nivel2(sf::RenderWindow& ventana, float ancho, float alto);

    void mostrar();
    void actualizar();
    void manejarEventos();

private:
    sf::RenderWindow& ventana;
    Musica musicaNivel2; // Objeto de la clase Musica para manejar la música del nivel 2
    sf::Texture fondoTextura;
    sf::Sprite fondoSprite;
    // Agrega más atributos según sea necesario
};

#endif // NIVEL2_H
