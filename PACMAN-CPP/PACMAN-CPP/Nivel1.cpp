#include "Nivel1.h"
#include <iostream>

Nivel1::Nivel1(sf::RenderWindow& ventana, float ancho, float alto) : ventana(ventana), jugador(ancho / 2, alto / 2, 5.0f) {
    if (!fondoTextura.loadFromFile("Nivel1/FondoNivel1.png")) {
        std::cerr << "Error al cargar la imagen de fondo." << std::endl;
    }

    fondoSprite.setTexture(fondoTextura);
    fondoSprite.setScale(ancho / fondoSprite.getGlobalBounds().width, alto / fondoSprite.getGlobalBounds().height);

    // Mapa del nivel
    mapa = new int* [altoMapa];
    for (int i = 0; i < altoMapa; ++i) {
        mapa[i] = new int[anchoMapa];
    }

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
    // TAMAÑO DEL MAPA
    anchoCelda = ventana.getSize().x / (anchoMapa * 2); 
    altoCelda = ventana.getSize().y / (altoMapa * 2.5); 

    // CENTRAR MAPA
    posXInicio = (ventana.getSize().x - (anchoCelda * anchoMapa)) / 2; 
    posYInicio = (ventana.getSize().y - (altoCelda * altoMapa)) / 2; 

    // Dibujar el mapa y el jugador
    for (int i = 0; i < altoMapa; ++i) {
        for (int j = 0; j < anchoMapa; ++j) {
            if (mapa[i][j] == 1) {
                // Dibujar una celda con colision
                sf::RectangleShape celda(sf::Vector2f(anchoCelda, altoCelda));
                celda.setPosition(posXInicio + j * anchoCelda, posYInicio + i * altoCelda);
                celda.setFillColor(sf::Color::Blue);
                ventana.draw(celda);
            }
        }
    }

    // Dibujar al jugador en su posicion actual
    jugador.dibujar(ventana);

    ventana.draw(fondoSprite);
    musicaNivel1.reproducir();
}

void Nivel1::actualizar() {
    // Obtener la posicion actual del jugador
    sf::Vector2f posicionActual = jugador.getPosicion();

    // Verificar si el jugador intenta moverse y la proxima posici�n es valida
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        jugador.mover(sf::Vector2f(0, -1), mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
        jugador.cambiarTextura("arriba.png");
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        jugador.mover(sf::Vector2f(0, 1), mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
        jugador.cambiarTextura("abajo.png");
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        jugador.mover(sf::Vector2f(-1, 0), mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
        jugador.cambiarTextura("izquierda.png");
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        jugador.mover(sf::Vector2f(1, 0), mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
        jugador.cambiarTextura("derecha.png");
    }
}

void Nivel1::manejarEventos() {
   
}

bool Nivel1::posicionValida(sf::Vector2f posicion) {
    // Convertir la posicion en la ventana a la posicion en la matriz
    int fila = static_cast<int>((posicion.y - posYInicio) / altoCelda);
    int columna = static_cast<int>((posicion.x - posXInicio) / anchoCelda);

    // Verificar si la posici�n esta dentro de los limites del mapa
    if (fila >= 0 && fila < altoMapa && columna >= 0 && columna < anchoMapa) {
        // Verificar si la posicion en la matriz es un espacio libre (0)
        return mapa[fila][columna] == 0;
    }

    // La posici�n est� fuera de los limites del mapa
    return false;
}