#include "Nivel1.h"
#include <iostream>

Nivel1::Nivel1(sf::RenderWindow& ventana, float ancho, float alto) : ventana(ventana) {
    if (!fondoTextura.loadFromFile("Nivel1/FondoNivel1.png")) {
        std::cerr << "Error al cargar la imagen de fondo." << std::endl;
        // Manejar el error apropiadamente (lanzar excepción, salida del programa, etc.)
    }

    fondoSprite.setTexture(fondoTextura);
    fondoSprite.setScale(ancho / fondoSprite.getGlobalBounds().width, alto / fondoSprite.getGlobalBounds().height);

    // Cargamos la música del nivel 1
    musicaNivel1.cargarMusicaNivel1();
}

void Nivel1::mostrar() {
    // Dibujar el fondo en la ventana del juego
    ventana.draw(fondoSprite); // Utiliza la ventana almacenada en el atributo de clase
    musicaNivel1.reproducir(); // Reproduce la música del nivel 1
}

void Nivel1::actualizar() {
    // Por el momento no necesitamos hacer nada en esta función
}

void Nivel1::manejarEventos() {
    // Implementar la lógica para manejar eventos del nivel 1
}
