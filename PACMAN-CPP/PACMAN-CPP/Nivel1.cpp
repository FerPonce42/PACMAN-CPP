#include "Nivel1.h"
#include <iostream>

Nivel1::Nivel1(sf::RenderWindow& ventana, float ancho, float alto)
    : ventana(ventana), fantasmaRojo(ancho / 2, alto / 2, 1.8f), jugador(ancho / 2, alto / 2 + 50, 1.8f), pelotas(nullptr), poderes(nullptr) {
    if (!fondoTextura.loadFromFile("Nivel1/FondoNivel1.png")) {
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

    if (!font.loadFromFile("Nivel1/fuentenivel1.ttf")) {
        std::cerr << "Error al cargar la fuente." << std::endl;
    }
    textoContador.setFont(font);
    textoContador.setCharacterSize(40);
    textoContador.setFillColor(sf::Color::White);
    textoContador.setPosition(290, 900);

    musicaNivel1.cargarMusicaNivel1();
}

Nivel1::~Nivel1() {
    for (int i = 0; i < altoMapa; ++i) {
        delete[] mapa[i];
    }
    delete[] mapa;
    delete pelotas;
    delete poderes;
}

// Método privado para inicializar el mapa del nivel
void Nivel1::inicializarMapa() {
    mapa = new int* [altoMapa];
    for (int i = 0; i < altoMapa; ++i) {
        mapa[i] = new int[anchoMapa];
    }

    int miMapa[12][30] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 2, 1, 0, 1, 1, 0, 1, 1, 1},
        {1, 3, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 3, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1},
        {1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
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
                celda.setFillColor(sf::Color(12, 34, 255));
                ventana.draw(celda);
            }
        }
    }
    // Dibuja las bolitas
    pelotas->dibujar(ventana);
    poderes->dibujar(ventana);  // Dibuja los poderes

    fantasmaRojo.dibujar(ventana);
    fantasmaRojo.dibujarVidas(ventana);

    jugador.dibujar(ventana);
    jugador.dibujarVidas(ventana);
    jugador.dibujarPuntaje(ventana);  // Dibuja el puntaje del Jugador

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


    // Reproduce la música del nivel
    musicaNivel1.reproducir();
}
void Nivel1::verificarColisiones() {
    // Verificar colisiones de jugador2 con las bolitas
    if (pelotas->verificarColision(jugador.getSprite())) {
        jugador.aumentarPuntaje(10);  // Aumentar puntaje en 10

        // Verificar si el jugador 2 ha comido todas las pelotas
        if (pelotas->getCantidadPelotas() == 0) {
            jugador.mostrarVentanaGanador(ventana, 2); // Jugador 2 (Pacman) ganó
        }
    }

    // Verificar colisiones de jugador2 con los poderes
    if (poderes->verificarColision(jugador.getSprite())) {
        // Poder activado
    }

    // Verificar colisiones entre jugador1 y jugador2
    if (fantasmaRojo.getSprite().getGlobalBounds().intersects(jugador.getSprite().getGlobalBounds())) {
        if (poderes->estaActivo()) {
            fantasmaRojo.reducirVida();
            if (fantasmaRojo.getVidas() <= 0) {
                jugador.mostrarVentanaGanador(ventana, 2); // Jugador 2 ganó
            }
            fantasmaRojo.setPosicionInicial();
        }
        else {
            jugador.reducirVida();
            if (jugador.getVidas() <= 0) {
                fantasmaRojo.mostrarVentanaGanador(ventana, 1); // Jugador 1 ganó
            }
            fantasmaRojo.setPosicionInicial();
            jugador.setPosicionInicial(); // Solo en este caso, cuando el jugador 2 mata al jugador 1, ambos regresan a su posición inicial
        }
    }
}


void Nivel1::actualizar() {
    float deltaTime = 1.0f / 60.0f;  // Asume 60 FPS para simplificar, deberías calcular el deltaTime real

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        fantasmaRojo.setDireccion(sf::Vector2f(0, -1));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        fantasmaRojo.setDireccion(sf::Vector2f(0, 1));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        fantasmaRojo.setDireccion(sf::Vector2f(-1, 0));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        fantasmaRojo.setDireccion(sf::Vector2f(1, 0));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        jugador.setDireccion(sf::Vector2f(0, -1));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        jugador.setDireccion(sf::Vector2f(0, 1));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        jugador.setDireccion(sf::Vector2f(-1, 0));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        jugador.setDireccion(sf::Vector2f(1, 0));
    }

    fantasmaRojo.mover(fantasmaRojo.getDireccion(), mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
    fantasmaRojo.actualizarAnimacion(deltaTime);

    jugador.mover(jugador.getDireccion(), mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
    jugador.actualizarAnimacion(deltaTime);

    if (poderes->estaActivo()) {
        // Limpiar los frames existentes antes de agregar nuevos frames
        fantasmaRojo.cambiarTexturaPorPoder();
        // Resto del código...
    }

    verificarColisiones();//COLISIONES ENTRE (JUGADOR1)FANTASMA Y (JUGADOR2)PACMAN Y BOLITAS
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