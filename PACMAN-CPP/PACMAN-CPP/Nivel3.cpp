#include "Nivel3.h"
#include <iostream>

Nivel3::Nivel3(sf::RenderWindow& ventana, float ancho, float alto) : ventana(ventana) {
    if (!fondoTextura.loadFromFile("Nivel3/FondoNivel3.png")) {
        std::cerr << "Error al cargar la imagen de fondo." << std::endl;
       
    }

    fondoSprite.setTexture(fondoTextura);
    fondoSprite.setScale(ancho / fondoSprite.getGlobalBounds().width, alto / fondoSprite.getGlobalBounds().height);

 
    musicaNivel3.cargarMusicaNivel3();
}

void Nivel3::mostrar() {
    
    ventana.draw(fondoSprite);
    musicaNivel3.reproducir(); 
}

void Nivel3::actualizar() {
    
}

void Nivel3::manejarEventos() {
    
}
