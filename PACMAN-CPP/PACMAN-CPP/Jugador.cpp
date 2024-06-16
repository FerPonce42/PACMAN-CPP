﻿#include "Jugador.h"
#include <iostream>

Jugador::Jugador(float x, float y, float velocidad)
    : velocidad(1.2), direccion(0, 0), vidas(3), posicionInicial(x, y), puntaje(0) { 
    animacion = new Animacion(0.1f);
    animacion->agregarFrame("Nivel1/Jugador/derecha1.png");
    animacion->agregarFrame("Nivel1/Jugador/derecha2.png");
    animacion->agregarFrame("Nivel1/Jugador/derecha3.png");

    sprite.setPosition(1040, 475); 
    sprite.setScale(0.8f, 0.8f);
}

void Jugador::aumentarPuntaje(int puntos) {
    puntaje += puntos;
}

int Jugador::getPuntaje() const {
    return puntaje;
}


int Jugador::getVidas() const {
    return vidas;
}

void Jugador::dibujarVidas(sf::RenderWindow& ventana) {
    sf::Font font;
    if (!font.loadFromFile("Nivel1/fuentenivel1.ttf")) {

    }
    sf::Text textoVidas;
    textoVidas.setFont(font);
    textoVidas.setString(std::to_string(vidas));
    textoVidas.setCharacterSize(40);
    textoVidas.setFillColor(sf::Color::White);
    textoVidas.setPosition(200, 900);

    ventana.draw(textoVidas);
}

void Jugador::reducirVida() {
    vidas--;
}

void Jugador::setPosicionInicial() {
    sprite.setPosition(1040, 475);
}

sf::Sprite& Jugador::getSprite() {
    return sprite;
}

void Jugador::mostrarVentanaGanador(sf::RenderWindow& mainWindow, int ganador) {
    Ganador ventanaGanador(mainWindow, ganador);
    int opcion = ventanaGanador.mostrar();

}
void Jugador::dibujarPuntaje(sf::RenderWindow& ventana) {
    sf::Font font;
    if (!font.loadFromFile("Nivel1/fuentenivel1.ttf")) {
        
    }
    sf::Text textoPuntaje;
    textoPuntaje.setFont(font);
    textoPuntaje.setString(std::to_string(puntaje));
    textoPuntaje.setCharacterSize(50);
    textoPuntaje.setFillColor(sf::Color::White);
    textoPuntaje.setPosition(250, 85);

    ventana.draw(textoPuntaje);
}


bool Jugador::posicionValida(sf::Vector2f nuevaPosicion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
    float jugadorAncho = sprite.getGlobalBounds().width;
    float jugadorAlto = sprite.getGlobalBounds().height;
    std::vector<sf::Vector2f> puntos;

    puntos.push_back(nuevaPosicion);
    puntos.push_back({ nuevaPosicion.x + jugadorAncho, nuevaPosicion.y });
    puntos.push_back({ nuevaPosicion.x, nuevaPosicion.y + jugadorAlto });
    puntos.push_back({ nuevaPosicion.x + jugadorAncho, nuevaPosicion.y + jugadorAlto });

    for (float x = nuevaPosicion.x + 1; x < nuevaPosicion.x + jugadorAncho; x += anchoCelda / 2) {
        puntos.push_back({ x, nuevaPosicion.y });
        puntos.push_back({ x, nuevaPosicion.y + jugadorAlto });
    }
    for (float y = nuevaPosicion.y + 1; y < nuevaPosicion.y + jugadorAlto; y += altoCelda / 2) {
        puntos.push_back({ nuevaPosicion.x, y });
        puntos.push_back({ nuevaPosicion.x + jugadorAncho, y });
    }

    for (auto& punto : puntos) {
        int columna = static_cast<int>((punto.x - posXInicio) / anchoCelda);
        int fila = static_cast<int>((punto.y - posYInicio) / altoCelda);

        if (fila < 0 || fila >= altoMapa || columna < 0 || columna >= anchoMapa || (mapa[fila][columna] != 0 && mapa[fila][columna] != 3)) {
            return false;
        }
    }

    return true;
}


void Jugador::mover(sf::Vector2f direccion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
    sf::Vector2f nuevaPosicion = sprite.getPosition() + direccion * velocidad;

    if (posicionValida(nuevaPosicion, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
        sprite.setPosition(nuevaPosicion);
    }
}

void Jugador::dibujar(sf::RenderWindow& ventana) {
    animacion->aplicarA(sprite);
    ventana.draw(sprite);
}

void Jugador::setDireccion(sf::Vector2f nuevaDireccion) {
    direccion = nuevaDireccion;
    
    delete animacion;
    animacion = new Animacion(0.1f); 

    if (direccion.x > 0) {
        animacion->agregarFrame("Nivel1/Jugador/derecha1.png");
        animacion->agregarFrame("Nivel1/Jugador/derecha2.png");
        animacion->agregarFrame("Nivel1/Jugador/derecha3.png");
    }
    else if (direccion.x < 0) {
        animacion->agregarFrame("Nivel1/Jugador/izquierda1.png");
        animacion->agregarFrame("Nivel1/Jugador/izquierda2.png");
        animacion->agregarFrame("Nivel1/Jugador/izquierda3.png");
    }
    else if (direccion.y > 0) {
        animacion->agregarFrame("Nivel1/Jugador/abajo1.png");
        animacion->agregarFrame("Nivel1/Jugador/abajo2.png");
        animacion->agregarFrame("Nivel1/Jugador/abajo3.png");
    }
    else if (direccion.y < 0) {
        animacion->agregarFrame("Nivel1/Jugador/arriba1.png");
        animacion->agregarFrame("Nivel1/Jugador/arriba2.png");
        animacion->agregarFrame("Nivel1/Jugador/arriba3.png");
    }
}

sf::Vector2f Jugador::getPosicion() const {
    return sprite.getPosition();
}

sf::Vector2f Jugador::getDireccion() const {
    return direccion;
}

void Jugador::actualizarAnimacion(float deltaTime) {
    animacion->actualizar(deltaTime);
}