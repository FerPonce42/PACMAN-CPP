#pragma once
#ifndef NIVEL1_H
#define NIVEL1_H

#include <SFML/Graphics.hpp>
#include "Musica.h" // Agregamos la inclusión de Musica.h

class Nivel1 {
public:
    Nivel1(sf::RenderWindow& ventana, float ancho, float alto);

    void mostrar();
    void actualizar();
    void manejarEventos();

private:
    sf::RenderWindow& ventana;
    Musica musicaNivel1; // Objeto de la clase Musica para manejar la música del nivel 1
    sf::Texture fondoTextura;
    sf::Sprite fondoSprite;
    // Agrega más atributos según sea necesario
};

#endif // NIVEL1_H
