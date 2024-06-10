#include "Nivel2.h"
#include <iostream>

Nivel2::Nivel2(sf::RenderWindow& ventana, float ancho, float alto)
    : ventana(ventana), fantasmaJugador(ancho / 2, alto / 2, 1.8f), pacmanIA(ancho / 2, alto / 2 + 50, 1.8f), pelotas(nullptr), poderes(nullptr) {
    if (!fondoTextura.loadFromFile("Nivel2/FondoNivel2.png")) {
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

    if (!font.loadFromFile("Nivel2/fuentenivel2.ttf")) {
        std::cerr << "Error al cargar la fuente." << std::endl;
    }
    textoContador.setFont(font);
    textoContador.setCharacterSize(40);
    textoContador.setFillColor(sf::Color::White);
    textoContador.setPosition(290, 900);

    musicaNivel2.cargarMusicaNivel2();
}

Nivel2::~Nivel2() {
    for (int i = 0; i < altoMapa; ++i) {
        delete[] mapa[i];
    }
    delete[] mapa;
    delete pelotas;
    delete poderes;
}

// Método privado para inicializar el mapa del nivel
void Nivel2::inicializarMapa() {
    mapa = new int* [altoMapa];
    for (int i = 0; i < altoMapa; ++i) {
        mapa[i] = new int[anchoMapa];
    }

    int miMapa[13][32] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1},
        {1, 1, 3, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 2, 1, 0, 1, 1, 1, 1, 1, 0, 1, 2, 1, 0, 1, 0, 3, 1},
        {1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1},
        {1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1},
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };


    // Copia el mapa predeterminado en el mapa del nivel
    for (int i = 0; i < altoMapa; ++i) {
        for (int j = 0; j < anchoMapa; ++j) {
            mapa[i][j] = miMapa[i][j];
        }
    }
}

// Método para mostrar el nivel en la ventana
void Nivel2::mostrar() {
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
                celda.setFillColor(sf::Color(255, 161, 61));
                ventana.draw(celda);
            }
        }
    }
    // Dibuja las bolitas
    pelotas->dibujar(ventana);
    poderes->dibujar(ventana);  // Dibuja los poderes

    fantasmaJugador.dibujar(ventana);
    fantasmaJugador.dibujarVidas(ventana);

    pacmanIA.dibujar(ventana);
    pacmanIA.dibujarVidas(ventana);
    pacmanIA.dibujarPuntaje(ventana);  // Dibuja el puntaje del Pacman

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
    musicaNivel2.reproducir();
}

void Nivel2::verificarColisiones() {
    // Verificar colisiones de PacmanIA con las bolitas
    if (pelotas->verificarColision(pacmanIA.getSprite())) {
        pacmanIA.aumentarPuntaje(10);  // Aumentar puntaje en 10

        // Verificar si el PacmanIA ha comido todas las pelotas
        if (pelotas->getCantidadPelotas() == 0) {
            pacmanIA.mostrarVentanaGanador(ventana, 2); // PacmanIA ganó
        }
    }

    // Verificar colisiones de PacmanIA con los poderes
    if (poderes->verificarColision(pacmanIA.getSprite())) {
        // Poder activado
    }

    // Verificar colisiones entre FantasmaJugador y PacmanIA
    if (fantasmaJugador.getSprite().getGlobalBounds().intersects(pacmanIA.getSprite().getGlobalBounds())) {
        if (poderes->estaActivo()) {
            fantasmaJugador.reducirVida();
            if (fantasmaJugador.getVidas() <= 0) {
                pacmanIA.mostrarVentanaGanador(ventana, 2); // PacmanIA ganó
            }
            fantasmaJugador.setPosicionInicial();
        }
        else {
            pacmanIA
                .reducirVida();
            if (pacmanIA.getVidas() <= 0) {
                fantasmaJugador.mostrarVentanaGanador(ventana, 1); // FantasmaJugador ganó
            }
            fantasmaJugador.setPosicionInicial();
            pacmanIA.setPosicionInicial(); // Solo en este caso, cuando PacmanIA es atrapado por el FantasmaJugador, ambos regresan a su posición inicial
        }
    }
}


void Nivel2::actualizar() {
    float deltaTime = 1.0f / 60.0f;  // Asume 60 FPS para simplificar, deberías calcular el deltaTime real

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        fantasmaJugador.setDireccion(sf::Vector2f(0, -1));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        fantasmaJugador.setDireccion(sf::Vector2f(0, 1));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        fantasmaJugador.setDireccion(sf::Vector2f(-1, 0));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        fantasmaJugador.setDireccion(sf::Vector2f(1, 0));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        pacmanIA.setDireccion(sf::Vector2f(0, -1));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        pacmanIA.setDireccion(sf::Vector2f(0, 1));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        pacmanIA.setDireccion(sf::Vector2f(-1, 0));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        pacmanIA.setDireccion(sf::Vector2f(1, 0));
    }

    fantasmaJugador.mover(fantasmaJugador.getDireccion(), mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
    fantasmaJugador.actualizarAnimacion(deltaTime);

    pacmanIA.mover(pacmanIA.getDireccion(), mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
    pacmanIA.actualizarAnimacion(deltaTime);

    if (poderes->estaActivo()) {
        // Limpiar los frames existentes antes de agregar nuevos frames
        fantasmaJugador.cambiarTexturaPorPoder();
        // Resto del código...
    }

    verificarColisiones(); // COLISIONES ENTRE (FANTASMAJUGADOR)FANTASMA Y (PACMANIA)PACMAN Y BOLITAS
}

// Método para manejar eventos de la ventana
void Nivel2::manejarEventos() {
    // Manejo de eventos (actualmente vacío)
}

// Método para verificar si una posición dada es válida en el nivel
bool Nivel2::posicionValida(sf::Vector2f posicion) {
    int fila = static_cast<int>((posicion.y - posYInicio) / altoCelda); // Calcula la fila en el mapa
    int columna = static_cast<int>((posicion.x - posXInicio) / anchoCelda); // Calcula la columna en el mapa

    // Verifica si la posición está dentro de los límites del mapa y si la celda es transitable (no hay obstáculo)
    if (fila >= 0 && fila < altoMapa && columna >= 0 && columna < anchoMapa) {
        return mapa[fila][columna] == 0;
    }

    return false;
}