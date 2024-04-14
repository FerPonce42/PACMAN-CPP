#pragma once
#ifndef NIVEL1_H
#define NIVEL1_H

#include <SFML/Graphics.hpp>
#include "Musica.h" // Agregamos la inclusi�n de Musica.h

class Nivel1 {
public:
    Nivel1(sf::RenderWindow& ventana, float ancho, float alto);

    void mostrar();
    void actualizar();
    void manejarEventos();

private:
    sf::RenderWindow& ventana;
    Musica musicaNivel1; // Objeto de la clase Musica para manejar la m�sica del nivel 1
    sf::Texture fondoTextura;
    sf::Sprite fondoSprite;
    // Agrega m�s atributos seg�n sea necesario
};

#endif // NIVEL1_H
