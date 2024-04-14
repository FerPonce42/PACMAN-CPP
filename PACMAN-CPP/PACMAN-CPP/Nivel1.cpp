#include "Nivel1.h"
#include <iostream>

Nivel1::Nivel1(sf::RenderWindow& ventana, float ancho, float alto) : ventana(ventana) {
    if (!fondoTextura.loadFromFile("Nivel1/FondoNivel1.png")) {
        std::cerr << "Error al cargar la imagen de fondo." << std::endl;
        
    }

    fondoSprite.setTexture(fondoTextura);
    fondoSprite.setScale(ancho / fondoSprite.getGlobalBounds().width, alto / fondoSprite.getGlobalBounds().height);

  
    musicaNivel1.cargarMusicaNivel1();
}

void Nivel1::mostrar() {
    
    ventana.draw(fondoSprite); 
    musicaNivel1.reproducir(); 
}

void Nivel1::actualizar() {
    
}

void Nivel1::manejarEventos() {
    
}
