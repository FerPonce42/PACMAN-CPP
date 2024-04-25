#include "Nivel1.h"
#include <iostream>

Nivel1::Nivel1(sf::RenderWindow& ventana, float ancho, float alto) : ventana(ventana), jugador(ancho / 2, alto / 2, 5.0f) {
    if (!fondoTextura.loadFromFile("Nivel1/FondoNivel1.png")) {
        std::cerr << "Error al cargar la imagen de fondo." << std::endl;
    }

    fondoSprite.setTexture(fondoTextura);
    fondoSprite.setScale(ancho / fondoSprite.getGlobalBounds().width, alto / fondoSprite.getGlobalBounds().height);


    int miMapa[12][30] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };


    // Copiar el mapa personalizado al mapa de la clase
    for (int i = 0; i < altoMapa; ++i) {
        for (int j = 0; j < anchoMapa; ++j) {
            mapa[i][j] = miMapa[i][j];
        }
    }

    musicaNivel1.cargarMusicaNivel1();
}

void Nivel1::mostrar() {
    // Calcular el tamaño de cada celda del mapa
    float anchoCelda = ventana.getSize().x / (anchoMapa * 2); // Reducir la escala a la cuarta parte
    float altoCelda = ventana.getSize().y / (altoMapa * 2); // Reducir la escala a la cuarta parte

    // Calcular la posición de inicio del mapa para centrarlo
    float posXInicio = (ventana.getSize().x - (anchoCelda * anchoMapa)) / 2; // Ajustar para centrar en el medio de la pantalla
    float posYInicio = (ventana.getSize().y - (altoCelda * altoMapa)) / 2; // Ajustar para centrar en el medio de la pantalla

    // Dibujar el mapa
    for (int i = 0; i < altoMapa; ++i) {
        for (int j = 0; j < anchoMapa; ++j) {
            if (mapa[i][j] == 1) {
                // Dibujar una celda con colisión
                sf::RectangleShape celda(sf::Vector2f(anchoCelda, altoCelda));
                celda.setPosition(posXInicio + j * anchoCelda, posYInicio + i * altoCelda); // Corregir la posición de las celdas
                celda.setFillColor(sf::Color::Blue); // Color de las celdas con colisión
                ventana.draw(celda);
            }
            // Si la celda es un 0, dibujar al jugador
            else if (mapa[i][j] == 0) {
                // Obtener la posición de la celda para dibujar al jugador
                float posX = posXInicio + j * anchoCelda + anchoCelda / 4; // Ajustar la posición del jugador
                float posY = posYInicio + i * altoCelda + altoCelda / 4; // Ajustar la posición del jugador
                // Establecer la dirección del jugador
                jugador.setDireccion(sf::Vector2f(posX, posY));
                // Dibujar al jugador
                jugador.dibujar(ventana);
            }
        }
    }

    // Resto del código de mostrar() permanece igual
    ventana.draw(fondoSprite);
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
    // Implementa el manejo de eventos aquí
}

