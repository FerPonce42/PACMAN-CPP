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


void Nivel2::inicializarMapa() {
    mapa = new int* [altoMapa];
    for (int i = 0; i < altoMapa; ++i) {
        mapa[i] = new int[anchoMapa];
    }

    int miMapa[13][32] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 3, 0, 1, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1},
        {1, 1, 1, 3, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1},
        {1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 2, 1, 0, 1, 1, 1, 1, 1, 0, 1, 2, 1, 0, 1, 3, 1, 1},
        {1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 2, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1},
        {1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1},
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 3, 0, 1, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };



    for (int i = 0; i < altoMapa; ++i) {
        for (int j = 0; j < anchoMapa; ++j) {
            mapa[i][j] = miMapa[i][j];
        }
    }
}


void Nivel2::mostrar() {
   
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
                celda.setFillColor(sf::Color(255, 161, 61));
                ventana.draw(celda);
            }
        }
    }
  
    pelotas->dibujar(ventana);
    poderes->dibujar(ventana);  

    fantasmaJugador.dibujar(ventana);
    fantasmaJugador.dibujarVidas(ventana);

    pacmanIA.dibujar(ventana);
    pacmanIA.dibujarVidas(ventana);
    pacmanIA.dibujarPuntaje(ventana);  

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

    
    musicaNivel2.reproducir();
}

void Nivel2::verificarColisiones() {
    
    if (pelotas->verificarColision(pacmanIA.getSprite())) {
        pacmanIA.aumentarPuntaje(10); 

        
        if (pelotas->getCantidadPelotas() == 0) {
            pacmanIA.mostrarVentanaGanador(ventana, 2); 
        }
    }

    
    if (poderes->verificarColision(pacmanIA.getSprite())) {
        
    }

    
    if (fantasmaJugador.getSprite().getGlobalBounds().intersects(pacmanIA.getSprite().getGlobalBounds())) {
        if (poderes->estaActivo()) {
            fantasmaJugador.reducirVida();
            if (fantasmaJugador.getVidas() <= 0) {
                pacmanIA.mostrarVentanaGanador(ventana, 2); 
            }
            fantasmaJugador.setPosicionInicial();
        }
        else {
            pacmanIA
                .reducirVida();
            if (pacmanIA.getVidas() <= 0) {
                fantasmaJugador.mostrarVentanaGanador(ventana, 1);
            }
            fantasmaJugador.setPosicionInicial();
            pacmanIA.setPosicionInicial(); 
        }
    }
}


void Nivel2::actualizar() {
    float deltaTime = 1.0f / 60.0f; 

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

    sf::Vector2f ghostPosition = fantasmaJugador.getSprite().getPosition();
    bool powerActive = poderes->estaActivo();

    pacmanIA.moverAI(mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio, ghostPosition, powerActive);
    pacmanIA.actualizarAnimacion(deltaTime);

    fantasmaJugador.mover(fantasmaJugador.getDireccion(), mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
    fantasmaJugador.actualizarAnimacion(deltaTime);

    if (poderes->estaActivo()) {
       
        fantasmaJugador.cambiarTexturaPorPoder();
        
    }

    verificarColisiones(); 
}


void Nivel2::manejarEventos() {
    
}


bool Nivel2::posicionValida(sf::Vector2f posicion) {
    int fila = static_cast<int>((posicion.y - posYInicio) / altoCelda);
    int columna = static_cast<int>((posicion.x - posXInicio) / anchoCelda);

  
    if (fila >= 0 && fila < altoMapa && columna >= 0 && columna < anchoMapa) {
        return mapa[fila][columna] == 0;
    }

    return false;
}