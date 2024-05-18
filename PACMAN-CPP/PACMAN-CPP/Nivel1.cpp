#include "Nivel1.h"
#include <iostream>

// Constructor de la clase Nivel1 que inicializa la ventana y crea un jugador en el centro de la ventana con una velocidad predeterminada
Nivel1::Nivel1(sf::RenderWindow& ventana, float ancho, float alto)
    : ventana(ventana), jugador(ancho / 2, alto / 2, 1.8f), fantasmaRojo("Nivel1/fantasma.png", ancho / 4, alto / 4, 1.5f) {
    // Carga la textura del fondo del nivel desde un archivo
    if (!fondoTextura.loadFromFile("Nivel1/FondoNivel1.png")) {
        std::cerr << "Error al cargar la imagen de fondo." << std::endl;
    }

    // Configura el sprite del fondo con la textura cargada y escala para que se ajuste a la ventana
    fondoSprite.setTexture(fondoTextura);
    fondoSprite.setScale(ancho / fondoSprite.getGlobalBounds().width, alto / fondoSprite.getGlobalBounds().height);

    // Inicializa el mapa del nivel
    inicializarMapa();

    // Carga la música del nivel
    musicaNivel1.cargarMusicaNivel1();
}


// Método privado para inicializar el mapa del nivel
void Nivel1::inicializarMapa() {
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

    // Copia el mapa predeterminado en el mapa del nivel
    for (int i = 0; i < altoMapa; ++i) {
        for (int j = 0; j < anchoMapa; ++j) {
            mapa[i][j] = miMapa[i][j];
        }
    }
}

// Método para mostrar el nivel en la ventana
void Nivel1::mostrar() {
    // Calcula el tamaño de cada celda del mapa y la posición inicial del mapa en la ventana
    anchoCelda = ventana.getSize().x / (anchoMapa * 1.8);
    altoCelda = ventana.getSize().y / (altoMapa * 2.6);
    posXInicio = (ventana.getSize().x - (anchoCelda * anchoMapa)) / 2;
    posYInicio = (ventana.getSize().y - (altoCelda * altoMapa)) / 2;

    // Dibuja el fondo del nivel en la ventana
    ventana.draw(fondoSprite);

    // Dibuja las celdas del mapa en la ventana
    for (int i = 0; i < altoMapa; ++i) {
        for (int j = 0; j < anchoMapa; ++j) {
            if (mapa[i][j] == 1) {
                sf::RectangleShape celda(sf::Vector2f(anchoCelda, altoCelda));
                celda.setPosition(posXInicio + j * anchoCelda, posYInicio + i * altoCelda);
                celda.setFillColor(sf::Color::Blue);
                ventana.draw(celda);
            }
        }
    }

    // Dibuja al jugador en la ventana
    jugador.dibujar(ventana);

    // Dibuja al fantasma en la ventana
    fantasmaRojo.dibujar(ventana);

    // Reproduce la música del nivel
    musicaNivel1.reproducir();
}



// Método para actualizar la lógica del nivel
void Nivel1::actualizar() {
    // Verifica las teclas presionadas para cambiar la dirección del jugador y su textura correspondiente
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        jugador.setDireccion(sf::Vector2f(0, -1));
        jugador.cambiarTextura("arriba.png");
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        jugador.setDireccion(sf::Vector2f(0, 1));
        jugador.cambiarTextura("abajo.png");
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        jugador.setDireccion(sf::Vector2f(-1, 0));
        jugador.cambiarTextura("izquierda.png");
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        jugador.setDireccion(sf::Vector2f(1, 0));
        jugador.cambiarTextura("derecha.png");
    }

    // Mover al jugador en la dirección actual
    jugador.mover(jugador.getDireccion(), mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);


}



// Método para manejar eventos de la ventana
void Nivel1::manejarEventos() {
    // Manejo de eventos (actualmente vacío)
}

// Método para verificar si una posición dada es válida en el nivel
bool Nivel1::posicionValida(sf::Vector2f posicion) {
    int fila = static_cast<int>((posicion.y - posYInicio) / altoCelda); // Calcula la fila en el mapa
    int columna = static_cast<int>((posicion.x - posXInicio) / anchoCelda); // Calcula la columna en el mapa

    // Verifica si la posición está dentro de los límites del mapa y si la celda es transitable (no hay obstáculo)
    if (fila >= 0 && fila < altoMapa && columna >= 0 && columna < anchoMapa) {
        return mapa[fila][columna] == 0;
    }

    return false;
}