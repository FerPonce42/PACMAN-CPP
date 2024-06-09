﻿#include "Nivel3.h"
#include <iostream>

Nivel3::Nivel3(sf::RenderWindow& ventana, float ancho, float alto)
    : ventana(ventana), jugador1(ancho / 2, alto / 2, 1.8f), jugador2(ancho / 2, alto / 2 + 50, 1.8f), pelotas(nullptr), poderes(nullptr) {
    if (!fondoTextura.loadFromFile("Nivel3/FondoNivel3.png")) {
        std::cerr << "Error al cargar la imagen de fondo." << std::endl;
    }

    fondoSprite.setTexture(fondoTextura);
    fondoSprite.setScale(ancho / fondoSprite.getGlobalBounds().width, alto / fondoSprite.getGlobalBounds().height);

    inicializarMapa();

    anchoCelda = ventana.getSize().x / (anchoMapa * 1.8);
    altoCelda = ventana.getSize().y / (altoMapa * 2.6);
    posXInicio = (ventana.getSize().x - (anchoCelda * anchoMapa)) / 2;
    posYInicio = (ventana.getSize().y - (altoCelda * altoMapa)) / 2;

    pelotas = new Pelotas(mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
    poderes = new Poderes(mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);

    if (!font.loadFromFile("Nivel3/fuentenivel3.ttf")) {
        std::cerr << "Error al cargar la fuente." << std::endl;
    }
    textoContador.setFont(font);
    textoContador.setCharacterSize(40);
    textoContador.setFillColor(sf::Color::White);
    textoContador.setPosition(250, 900);

    musicaNivel3.cargarMusicaNivel3();
}

Nivel3::~Nivel3() {
    for (int i = 0; i < altoMapa; ++i) {
        delete[] mapa[i];
    }
    delete[] mapa;
    delete pelotas;
    delete poderes;
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
        {1, 0, 1, 0, 1, 2, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 1, 0, 0, 0, 1},//5
        {1, 1, 1, 0, 1, 2, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 2, 1, 0, 1, 1, 0, 0, 1, 2, 1, 0, 1, 1, 1},//6
        {1, 3, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 0, 3, 1},//7
        {1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 3, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1},//8
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
    // Dibuja las bolitas
    pelotas->dibujar(ventana);
    poderes->dibujar(ventana);  // Dibuja los poderes

    jugador1.dibujar(ventana);
    jugador1.dibujarVidas(ventana);

    jugador2.dibujar(ventana);
    jugador2.dibujarVidas(ventana);
    jugador2.dibujarPuntaje(ventana);  // Dibuja el puntaje del Jugador 2

    if (poderes->estaActivo()) {
        // Obtener el tiempo transcurrido desde que se activó el poder
        float tiempoTranscurrido = relojContador.getElapsedTime().asSeconds();

        // Calcular los segundos restantes (iniciando en 5)
        int segundosRestantes = 5 - static_cast<int>(tiempoTranscurrido);

        // Si los segundos restantes son menores o iguales a 0, reiniciar el contador
        if (segundosRestantes <= 0) {
            relojContador.restart();
            segundosRestantes = 5;
        }

        // Actualizar el texto del contador
        textoContador.setString(std::to_string(segundosRestantes) + "s");
        ventana.draw(textoContador);
    }


    // Reproduce la m�sica del nivel
    musicaNivel3.reproducir();
}
void Nivel3::verificarColisiones() {
    // Verificar colisiones de jugador2 con las bolitas
    if (pelotas->verificarColision(jugador2.getSprite())) {
        jugador2.aumentarPuntaje(10);  // Aumentar puntaje en 10

        // Verificar si el jugador 2 ha comido todas las pelotas
        if (pelotas->getCantidadPelotas() == 0) {
            jugador2.mostrarVentanaGanador(ventana, 2); // Jugador 2 (Pacman) ganó
        }
    }

    // Verificar colisiones de jugador2 con los poderes
    if (poderes->verificarColision(jugador2.getSprite())) {
        // Poder activado
    }

    // Verificar colisiones entre jugador1 y jugador2
    if (jugador1.getSprite().getGlobalBounds().intersects(jugador2.getSprite().getGlobalBounds())) {
        if (poderes->estaActivo()) {
            jugador1.reducirVida();
            if (jugador1.getVidas() <= 0) {
                jugador2.mostrarVentanaGanador(ventana, 2); // Jugador 2 ganó
            }
            jugador1.setPosicionInicial();
        }
        else {
            jugador2.reducirVida();
            if (jugador2.getVidas() <= 0) {
                jugador1.mostrarVentanaGanador(ventana, 1); // Jugador 1 ganó
            }
            jugador1.setPosicionInicial();
            jugador2.setPosicionInicial(); // Solo en este caso, cuando el jugador 2 mata al jugador 1, ambos regresan a su posición inicial
        }
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

    verificarColisiones();//COLISIONES ENTRE (JUGADOR1)FANTASMA Y (JUGADOR2)PACMAN Y BOLITAS
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