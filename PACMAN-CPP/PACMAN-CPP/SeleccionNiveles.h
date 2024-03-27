
#ifndef NIVELMENU_H
#define NIVELMENU_H

#include <SFML/Graphics.hpp>

class SeleccionNiveles {
public:
    SeleccionNiveles(float ancho, float alto); 
    void dibujar(sf::RenderWindow& ventana); 
    void moverArriba(); 
    void moverAbajo(); 
    int obtenerNivelSeleccionado(); 
    bool seSeleccionoRetroceder();

private:
    int indiceNivelSeleccionado; 
    sf::Font fuente; 
    sf::Text textoNivel[5]; 
    sf::Texture texturaFondo; 
    sf::Sprite spriteFondo; 
};

#endif