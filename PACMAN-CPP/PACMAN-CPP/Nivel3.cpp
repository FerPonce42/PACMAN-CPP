#include "Nivel3.h"
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
    textoContador.setPosition(290, 900);

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


void Nivel3::inicializarMapa() {
    mapa = new int* [altoMapa];
    for (int i = 0; i < altoMapa; ++i) {
        mapa[i] = new int[anchoMapa];
    }

    int miMapa[12][30] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1},
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 2, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 2, 1, 0, 1, 2, 1, 0, 1, 2, 1, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 2, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 2, 1, 0, 1, 1, 0, 0, 1, 2, 1, 0, 1, 1, 1},
        {1, 3, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 2, 1, 0, 0, 3, 1},
        {1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 3, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };


    
    for (int i = 0; i < altoMapa; ++i) {
        for (int j = 0; j < anchoMapa; ++j) {
            mapa[i][j] = miMapa[i][j];
        }
    }
}


void Nivel3::mostrar() {
    
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
                celda.setFillColor(sf::Color(244, 28, 77));
                ventana.draw(celda);
            }
        }
    }
    
    pelotas->dibujar(ventana);
    poderes->dibujar(ventana);  

    jugador1.dibujar(ventana);
    jugador1.dibujarVidas(ventana);

    jugador2.dibujar(ventana);
    jugador2.dibujarVidas(ventana);
    jugador2.dibujarPuntaje(ventana); 

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


  
    musicaNivel3.reproducir();
}
void Nivel3::verificarColisiones() {
    
    if (pelotas->verificarColision(jugador2.getSprite())) {
        jugador2.aumentarPuntaje(10);  

       
        if (pelotas->getCantidadPelotas() == 0) {
            jugador2.mostrarVentanaGanador(ventana, 2); 
        }
    }

    
    if (poderes->verificarColision(jugador2.getSprite())) {
       
    }

   
    if (jugador1.getSprite().getGlobalBounds().intersects(jugador2.getSprite().getGlobalBounds())) {
        if (poderes->estaActivo()) {
            jugador1.reducirVida();
            if (jugador1.getVidas() <= 0) {
                jugador2.mostrarVentanaGanador(ventana, 2); 
            }
            jugador1.setPosicionInicial();
        }
        else {
            jugador2.reducirVida();
            if (jugador2.getVidas() <= 0) {
                jugador1.mostrarVentanaGanador(ventana, 1); 
            }
            jugador1.setPosicionInicial();
            jugador2.setPosicionInicial(); 
        }
    }
}


void Nivel3::actualizar() {
    float deltaTime = 1.0f / 60.0f; 

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

    if (poderes->estaActivo()) {
        
        jugador1.cambiarTexturaPorPoder();
        
    }

    verificarColisiones();
}


void Nivel3::manejarEventos() {
    
}


bool Nivel3::posicionValida(sf::Vector2f posicion) {
    int fila = static_cast<int>((posicion.y - posYInicio) / altoCelda); 
    int columna = static_cast<int>((posicion.x - posXInicio) / anchoCelda); 

    
    if (fila >= 0 && fila < altoMapa && columna >= 0 && columna < anchoMapa) {
        return mapa[fila][columna] == 0;
    }

    return false;
}