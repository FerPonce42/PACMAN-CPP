#include "Nivel2.h"
#include <iostream>

Nivel2::Nivel2(sf::RenderWindow& ventana, float ancho, float alto) : ventana(ventana) {
    if (!fondoTextura.loadFromFile("Nivel2/FondoNivel2.png")) {
        std::cerr << "Error al cargar la imagen de fondo." << std::endl;
        
    }

    fondoSprite.setTexture(fondoTextura);
    fondoSprite.setScale(ancho / fondoSprite.getGlobalBounds().width, alto / fondoSprite.getGlobalBounds().height);

    musicaNivel2.cargarMusicaNivel2();
}

void Nivel2::mostrar() {
    
    ventana.draw(fondoSprite); 
    musicaNivel2.reproducir(); 
}

void Nivel2::actualizar() {
    
}

void Nivel2::manejarEventos() {
   
}
