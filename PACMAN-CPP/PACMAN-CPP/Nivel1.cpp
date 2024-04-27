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
    anchoCelda = ventana.getSize().x / (anchoMapa * 2); // Reducir la escala a la cuarta parte
    altoCelda = ventana.getSize().y / (altoMapa * 2.5); // Reducir la escala a la cuarta parte

    // Calcular la posición de inicio del mapa para centrarlo
    posXInicio = (ventana.getSize().x - (anchoCelda * anchoMapa)) / 2; // Ajustar para centrar en el medio de la pantalla
    posYInicio = (ventana.getSize().y - (altoCelda * altoMapa)) / 2; // Ajustar para centrar en el medio de la pantalla

    // Dibujar el mapa y el jugador
    for (int i = 0; i < altoMapa; ++i) {
        for (int j = 0; j < anchoMapa; ++j) {
            if (mapa[i][j] == 1) {
                // Dibujar una celda con colisión
                sf::RectangleShape celda(sf::Vector2f(anchoCelda, altoCelda));
                celda.setPosition(posXInicio + j * anchoCelda, posYInicio + i * altoCelda);
                celda.setFillColor(sf::Color::Blue);
                ventana.draw(celda);
            }
            else if (mapa[i][j] == 0) {
                // Si la celda es un espacio libre, no hacemos nada, ya que el jugador se dibujará en esa posición
            }
        }
    }

    // Dibujar al jugador en su posición actual
    jugador.dibujar(ventana);

    // Resto del código de mostrar() permanece igual
    ventana.draw(fondoSprite);
    musicaNivel1.reproducir();
}



void Nivel1::actualizar() {
    // Obtener la posición actual del jugador
    sf::Vector2f posicionActual = jugador.getPosicion();

    // Verificar si el jugador intenta moverse hacia arriba y la próxima posición es válida
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && posicionValida(sf::Vector2f(posicionActual.x, posicionActual.y - 1))) {
        jugador.mover(sf::Vector2f(0, -1));
        jugador.cambiarTextura("arriba.png");
    }

    // Verificar si el jugador intenta moverse hacia abajo y la próxima posición es válida
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && posicionValida(sf::Vector2f(posicionActual.x, posicionActual.y + 1))) {
        jugador.mover(sf::Vector2f(0, 1));
        jugador.cambiarTextura("abajo.png");
    }

    // Verificar si el jugador intenta moverse hacia la izquierda y la próxima posición es válida
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && posicionValida(sf::Vector2f(posicionActual.x - 1, posicionActual.y))) {
        jugador.mover(sf::Vector2f(-1, 0));
        jugador.cambiarTextura("izquierda.png");
    }

    // Verificar si el jugador intenta moverse hacia la derecha y la próxima posición es válida
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && posicionValida(sf::Vector2f(posicionActual.x + 1, posicionActual.y))) {
        jugador.mover(sf::Vector2f(1, 0));
        jugador.cambiarTextura("derecha.png");
    }
}

// Método para verificar si una posición en la matriz es válida (0 significa espacio libre)
bool Nivel1::posicionValida(sf::Vector2f posicion) {
    // Convertir la posición en la ventana a la posición en la matriz
    int fila = static_cast<int>((posicion.y - posYInicio) / altoCelda);
    int columna = static_cast<int>((posicion.x - posXInicio) / anchoCelda);

    // Verificar si la posición está dentro de los límites del mapa
    if (fila >= 0 && fila < altoMapa && columna >= 0 && columna < anchoMapa) {
        // Verificar si la posición en la matriz es un espacio libre (0)
        return mapa[fila][columna] == 0;
    }

    // La posición está fuera de los límites del mapa
    return false;
}


void Nivel1::manejarEventos() {
    // Implementa el manejo de eventos aquí
}

