#include "Nivel1.h"
#include <iostream>

Nivel1::Nivel1(sf::RenderWindow& ventana, float ancho, float alto) : ventana(ventana), jugador(ancho / 2, alto / 2, 5.0f) {
    if (!fondoTextura.loadFromFile("Nivel1/FondoNivel1.png")) {
        std::cerr << "Error al cargar la imagen de fondo." << std::endl;
    }

    fondoSprite.setTexture(fondoTextura);
    fondoSprite.setScale(ancho / fondoSprite.getGlobalBounds().width, alto / fondoSprite.getGlobalBounds().height);

    musicaNivel1.cargarMusicaNivel1();
}

void Nivel1::mostrar() {
    ventana.draw(fondoSprite);
    jugador.dibujar(ventana);
    musicaNivel1.reproducir();
}

void Nivel1::actualizar() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        jugador.mover(sf::Vector2f(0, -1));
        jugador.cambiarTextura("arriba.png");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        jugador.mover(sf::Vector2f(0, 1));
        jugador.cambiarTextura("abajo.png");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        jugador.mover(sf::Vector2f(-1, 0));
        jugador.cambiarTextura("izquierda.png");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        jugador.mover(sf::Vector2f(1, 0));
        jugador.cambiarTextura("derecha.png");
    }
}

void Nivel1::manejarEventos() {

}