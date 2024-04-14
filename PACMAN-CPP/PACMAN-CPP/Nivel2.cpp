#include "Nivel2.h"
#include <iostream>

Nivel2::Nivel2(sf::RenderWindow& ventana, float ancho, float alto) : ventana(ventana) {
    if (!fondoTextura.loadFromFile("Nivel2/FondoNivel2.png")) {
        std::cerr << "Error al cargar la imagen de fondo." << std::endl;
        // Manejar el error apropiadamente (lanzar excepción, salida del programa, etc.)
    }

    fondoSprite.setTexture(fondoTextura);
    fondoSprite.setScale(ancho / fondoSprite.getGlobalBounds().width, alto / fondoSprite.getGlobalBounds().height);

    // Cargamos la música del nivel 2
    musicaNivel2.cargarMusicaNivel2();
}

void Nivel2::mostrar() {
    // Dibujar el fondo en la ventana del juego
    ventana.draw(fondoSprite); // Utiliza la ventana almacenada en el atributo de clase
    musicaNivel2.reproducir(); // Reproduce la música del nivel 2
}

void Nivel2::actualizar() {
    // Por el momento no necesitamos hacer nada en esta función
}

void Nivel2::manejarEventos() {
    // Implementar la lógica para manejar eventos del nivel 2
}
