#pragma once
#ifndef NIVEL1_H
#define NIVEL1_H

#include <SFML/Graphics.hpp>

class Nivel1 {
public:
    Nivel1(sf::RenderWindow& ventana, float ancho, float alto);

    void mostrar();
    void actualizar();
    void manejarEventos();

private:
    sf::RenderWindow& ventana;
    sf::Texture fondoTextura;
    sf::Sprite fondoSprite;
    // Agrega m�s atributos seg�n sea necesario
};

#endif // NIVEL1_H
