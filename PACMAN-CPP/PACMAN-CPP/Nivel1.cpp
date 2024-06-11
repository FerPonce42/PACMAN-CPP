#include "Nivel1.h"
#include <iostream>

Nivel1::Nivel1(sf::RenderWindow& ventana, float ancho, float alto)
    : ventana(ventana), fantasmaRojo(ancho / 2, alto / 2, 1.8f), fantasmaCeleste(ancho / 2, alto / 2 + 50, 1.8f), fantasmaRosa(ancho / 2, alto / 2 + 100, 1.8f), fantasmaNaranja(ancho / 2, alto / 2 + 150, 1.8f), jugador(ancho / 2, alto / 2 + 200, 1.8f), pelotas(nullptr), poderes(nullptr) {
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

    for (int i = 0; i < altoMapa; ++i) {
        for (int j = 0; j < anchoMapa; ++j) {
            mapa[i][j] = miMapa[i][j];
        }
    }
}

void Nivel1::mostrar() {
    anchoCelda = ventana.getSize().x / (anchoMapa * 1.8);
    altoCelda = ventana.getSize().y / (altoMapa * 2.6);
    posXInicio = (ventana.getSize().x - (anchoCelda * anchoMapa)) / 2;
    posYInicio = (ventana.getSize().y - (altoCelda * altoMapa)) / 2;

    ventana.draw(fondoSprite);

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

    pelotas->dibujar(ventana);
    poderes->dibujar(ventana);

    fantasmaRojo.dibujar(ventana);
    fantasmaRojo.dibujarVidas(ventana);

    fantasmaCeleste.dibujar(ventana); // Dibuja el fantasma celeste
    fantasmaRosa.dibujar(ventana);
    fantasmaNaranja.dibujar(ventana);

    jugador.dibujar(ventana);
    jugador.dibujarVidas(ventana);
    jugador.dibujarPuntaje(ventana);

    if (poderes->estaActivo()) {
        float tiempoTranscurrido = relojContador.getElapsedTime().asSeconds();
        int segundosRestantes = 5 - static_cast<int>(tiempoTranscurrido);

        if (segundosRestantes <= 0) {
            relojContador.restart();
            segundosRestantes = 5;
        }

        textoContador.setString(std::to_string(segundosRestantes) + "s");
        ventana.draw(textoContador);
    }

    musicaNivel1.reproducir();
}

void Nivel1::verificarColisiones() {
    if (pelotas->verificarColision(jugador.getSprite())) {
        jugador.aumentarPuntaje(10);

        if (pelotas->getCantidadPelotas() == 0) {
            jugador.mostrarVentanaGanador(ventana, 2);
        }
    }

    if (poderes->verificarColision(jugador.getSprite())) {
        // Poder activado
    }

    if (fantasmaRojo.getSprite().getGlobalBounds().intersects(jugador.getSprite().getGlobalBounds())) {
        if (poderes->estaActivo()) {
            fantasmaRojo.reducirVida();
            if (fantasmaRojo.getVidas() <= 0) {
                jugador.mostrarVentanaGanador(ventana, 2);
            }
            fantasmaRojo.setPosicionInicial();
        }
        else {
            jugador.reducirVida();
            if (jugador.getVidas() <= 0) {
                fantasmaRojo.mostrarVentanaGanador(ventana, 1);
            }
            fantasmaRojo.setPosicionInicial();
            jugador.setPosicionInicial();
        }
    }

    if (fantasmaCeleste.getSprite().getGlobalBounds().intersects(jugador.getSprite().getGlobalBounds())) {
        if (poderes->estaActivo()) {
            fantasmaCeleste.reducirVida();
            if (fantasmaCeleste.getVidas() <= 0) {
                jugador.mostrarVentanaGanador(ventana, 2);
            }
            fantasmaCeleste.setPosicionInicial();
        }
        else {
            jugador.reducirVida();
            if (jugador.getVidas() <= 0) {
                fantasmaCeleste.mostrarVentanaGanador(ventana, 1);
            }
            fantasmaCeleste.setPosicionInicial();
            jugador.setPosicionInicial();
        }
    }
    if (fantasmaRosa.getSprite().getGlobalBounds().intersects(jugador.getSprite().getGlobalBounds())) {
        if (poderes->estaActivo()) {
            fantasmaRosa.reducirVida();
            if (fantasmaRosa.getVidas() <= 0) {
                jugador.mostrarVentanaGanador(ventana, 2);
            }
            fantasmaRosa.setPosicionInicial();
        }
        else {
            jugador.reducirVida();
            if (jugador.getVidas() <= 0) {
                fantasmaRosa.mostrarVentanaGanador(ventana, 1);
            }
            fantasmaRosa.setPosicionInicial();
            jugador.setPosicionInicial();
        }
    }

    if (fantasmaNaranja.getSprite().getGlobalBounds().intersects(jugador.getSprite().getGlobalBounds())) {
        if (poderes->estaActivo()) {
            fantasmaNaranja.reducirVida();
            if (fantasmaNaranja.getVidas() <= 0) {
                jugador.mostrarVentanaGanador(ventana, 2);
            }
            fantasmaNaranja.setPosicionInicial();
        }
        else {
            jugador.reducirVida();
            if (jugador.getVidas() <= 0) {
                fantasmaNaranja.mostrarVentanaGanador(ventana, 1);
            }
            fantasmaNaranja.setPosicionInicial();
            jugador.setPosicionInicial();
        }
    }
}

void Nivel1::actualizar() {
    float deltaTime = 1.0f / 60.0f;

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

    fantasmaRojo.moverAI(mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio, jugador.getPosicion(), poderes->estaActivo());
    fantasmaRojo.actualizarAnimacion(deltaTime);

    fantasmaCeleste.moverAI(mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio, jugador.getPosicion(), poderes->estaActivo());
    fantasmaCeleste.actualizarAnimacion(deltaTime);

    fantasmaRosa.moverAI(mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio, jugador.getPosicion(), poderes->estaActivo());
    fantasmaRosa.actualizarAnimacion(deltaTime);

    fantasmaNaranja.moverAI(mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio, jugador.getPosicion(), poderes->estaActivo());
    fantasmaNaranja.actualizarAnimacion(deltaTime);

    jugador.mover(jugador.getDireccion(), mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
    jugador.actualizarAnimacion(deltaTime);

    verificarColisiones();
}

void Nivel1::manejarEventos() {
    sf::Event event;
    while (ventana.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            ventana.close();
        }
    }
}

bool Nivel1::posicionValida(sf::Vector2f posicion) {
    int fila = static_cast<int>((posicion.y - posYInicio) / altoCelda);
    int columna = static_cast<int>((posicion.x - posXInicio) / anchoCelda);

    if (fila >= 0 && fila < altoMapa && columna >= 0 && columna < anchoMapa) {
        return mapa[fila][columna] == 0;
    }

    return false;
}
