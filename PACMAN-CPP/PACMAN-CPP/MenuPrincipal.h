
#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include <SFML/Graphics.hpp>

class MenuPrincipal {
public:
    MenuPrincipal(float ancho, float alto); 

    void dibujar(sf::RenderWindow& ventana); 
    void moverArriba(); 
    void moverAbajo(); 
    int obtenerOpcionSeleccionada(); 

private:
    int indiceItemSeleccionado; 
    sf::Font fuente; 
    sf::Text textoMenu[5]; 
    sf::Texture texturaFondo; 
    sf::Sprite spriteFondo; 
};

#endif