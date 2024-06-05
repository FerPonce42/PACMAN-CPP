#include "Nivel3.h"
#include <iostream>

// Constructor de la clase Nivel3 que inicializa la ventana y crea los jugadores en el centro de la ventana con una velocidad predeterminada
Nivel3::Nivel3(sf::RenderWindow& ventana, float ancho, float alto)
    : ventana(ventana), jugador1(ancho / 2, alto / 2, 1.8f), jugador2(ancho / 2, alto / 2 + 50, 1.8f) {
    // Carga la textura del fondo del nivel desde un archivo
    if (!fondoTextura.loadFromFile("Nivel3/FondoNivel3.png")) {
        std::cerr << "Error al cargar la imagen de fondo." << std::endl;
    }

    // Configura el sprite del fondo con la textura cargada y escala para que se ajuste a la ventana
    fondoSprite.setTexture(fondoTextura);
    fondoSprite.setScale(ancho / fondoSprite.getGlobalBounds().width, alto / fondoSprite.getGlobalBounds().height);

    // Inicializa el mapa del nivel
    inicializarMapa();

    // Carga la m�sica del nivel
    musicaNivel3.cargarMusicaNivel3();
}

// M�todo privado para inicializar el mapa del nivel
void Nivel3::inicializarMapa() {
    mapa = new int* [altoMapa];
    for (int i = 0; i < altoMapa; ++i) {
        mapa[i] = new int[anchoMapa];
    }

    int miMapa[12][30] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//1 LISTO
        {1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1},//2 LISTO
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},//3 LISTO
        {1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},//4 LIXTO CALISTO
        {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},//5
        {1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1},//6
        {1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},//7
        {1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1},//8
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},//9
        {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1},//10
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},//11
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}//12
    };


    // Copia el mapa predeterminado en el mapa del nivel
    for (int i = 0; i < altoMapa; ++i) {
        for (int j = 0; j < anchoMapa; ++j) {
            mapa[i][j] = miMapa[i][j];
        }
    }
}

// M�todo para mostrar el nivel en la ventana
void Nivel3::mostrar() {
    // Calcula el tama�o de cada celda del mapa y la posici�n inicial del mapa en la ventana
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
                celda.setFillColor(sf::Color::Magenta);
                ventana.draw(celda);
            }
        }
    }

    // Dibuja a los jugadores en la ventana
    jugador1.dibujar(ventana);
    jugador1.dibujarVidas(ventana);

    jugador2.dibujar(ventana);
    jugador2.dibujarVidas(ventana);
    // Reproduce la m�sica del nivel
    musicaNivel3.reproducir();
}
void Nivel3::verificarColisiones() {
    if (jugador1.getSprite().getGlobalBounds().intersects(jugador2.getSprite().getGlobalBounds())) {
        jugador2.reducirVida();
        jugador1.setPosicionInicial();
        jugador2.setPosicionInicial();
    }
}


void Nivel3::actualizar() {
    float deltaTime = 1.0f / 60.0f;  // Asume 60 FPS para simplificar, deber�as calcular el deltaTime real

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        jugador1.setDireccion(sf::Vector2f(0, -1));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        jugador1.setDireccion(sf::Vector2f(0, 1));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        jugador1.setDireccion(sf::Vector2f(-1, 0));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        jugador1.setDireccion(sf::Vector2f(1, 0));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        jugador2.setDireccion(sf::Vector2f(0, -1));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        jugador2.setDireccion(sf::Vector2f(0, 1));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        jugador2.setDireccion(sf::Vector2f(-1, 0));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        jugador2.setDireccion(sf::Vector2f(1, 0));
    }

    jugador1.mover(jugador1.getDireccion(), mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
    jugador1.actualizarAnimacion(deltaTime);

    jugador2.mover(jugador2.getDireccion(), mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
    jugador2.actualizarAnimacion(deltaTime);

    verificarColisiones();//COLISIONES ENTRE (JUGADOR1)FANTASMA Y (JUGADOR2)PACMAN
}

// M�todo para manejar eventos de la ventana
void Nivel3::manejarEventos() {
    // Manejo de eventos (actualmente vac�o)
}

// M�todo para verificar si una posici�n dada es v�lida en el nivel
bool Nivel3::posicionValida(sf::Vector2f posicion) {
    int fila = static_cast<int>((posicion.y - posYInicio) / altoCelda); // Calcula la fila en el mapa
    int columna = static_cast<int>((posicion.x - posXInicio) / anchoCelda); // Calcula la columna en el mapa

    // Verifica si la posici�n est� dentro de los l�mites del mapa y si la celda es transitable (no hay obst�culo)
    if (fila >= 0 && fila < altoMapa && columna >= 0 && columna < anchoMapa) {
        return mapa[fila][columna] == 0;
    }

    return false;
}