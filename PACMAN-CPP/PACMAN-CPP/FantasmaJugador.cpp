#include "FantasmaJugador.h"
#include <iostream>

FantasmaJugador::FantasmaJugador(float x, float y, float velocidad)
    : velocidad(velocidad), direccion(0, 0), vidas(3), posicionInicial(x, y) { 
    animacion = new Animacion(0.1f);  
    animacion->agregarFrame("Nivel2/FantasmaJugador/derecha1.png");
    animacion->agregarFrame("Nivel2/FantasmaJugador/derecha2.png");
    animacion->agregarFrame("Nivel2/FantasmaJugador/derecha3.png");

    sprite.setPosition(1100, 495); 
    sprite.setScale(0.8f, 0.8f);
}

int FantasmaJugador::getVidas() const {
    return vidas;
}

void FantasmaJugador::dibujarVidas(sf::RenderWindow& ventana) {
    sf::Font font;
    if (!font.loadFromFile("Nivel2/fuentenivel2.ttf")) {

    }
    sf::Text textoVidas;
    textoVidas.setFont(font);
    textoVidas.setString(std::to_string(vidas));
    textoVidas.setCharacterSize(40);
    textoVidas.setFillColor(sf::Color::White);
    textoVidas.setPosition(200, 825);

    ventana.draw(textoVidas);
}

void FantasmaJugador::reducirVida() {
    vidas--;
}

void FantasmaJugador::setPosicionInicial() {
    sprite.setPosition(1100, 495);
}

sf::Sprite& FantasmaJugador::getSprite() {
    return sprite;
}

void FantasmaJugador::cambiarTexturaPorPoder() {
    
    animacion->limpiarFrames();
    animacion->agregarFrame("Nivel2/FantasmaJugador/perseguido1.png");
    animacion->agregarFrame("Nivel2/FantasmaJugador/perseguido2.png");
    animacion->agregarFrame("Nivel2/FantasmaJugador/perseguido3.png");
    
}

void FantasmaJugador::mostrarVentanaGanador(sf::RenderWindow& mainWindow, int ganador) {
    Ganador ventanaGanador(mainWindow, ganador);
    int opcion = ventanaGanador.mostrar();

}

bool FantasmaJugador::posicionValida(sf::Vector2f nuevaPosicion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
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


void FantasmaJugador::mover(sf::Vector2f direccion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
    sf::Vector2f nuevaPosicion = sprite.getPosition() + direccion * velocidad;

    if (posicionValida(nuevaPosicion, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
        sprite.setPosition(nuevaPosicion);
    }
}

void FantasmaJugador::dibujar(sf::RenderWindow& ventana) {
    animacion->aplicarA(sprite);
    ventana.draw(sprite);
}

void FantasmaJugador::setDireccion(sf::Vector2f nuevaDireccion) {
    direccion = nuevaDireccion;
    
    delete animacion;
    animacion = new Animacion(0.1f);  

    if (direccion.x > 0) {
        animacion->agregarFrame("Nivel2/FantasmaJugador/derecha1.png");
        animacion->agregarFrame("Nivel2/FantasmaJugador/derecha2.png");
        animacion->agregarFrame("Nivel2/FantasmaJugador/derecha3.png");
    }
    else if (direccion.x < 0) {
        animacion->agregarFrame("Nivel2/FantasmaJugador/izquierda1.png");
        animacion->agregarFrame("Nivel2/FantasmaJugador/izquierda2.png");
        animacion->agregarFrame("Nivel2/FantasmaJugador/izquierda3.png");
    }
    else if (direccion.y > 0) {
        animacion->agregarFrame("Nivel2/FantasmaJugador/abajo1.png");
        animacion->agregarFrame("Nivel2/FantasmaJugador/abajo2.png");
        animacion->agregarFrame("Nivel2/FantasmaJugador/abajo3.png");
    }
    else if (direccion.y < 0) {
        animacion->agregarFrame("Nivel2/FantasmaJugador/arriba1.png");
        animacion->agregarFrame("Nivel2/FantasmaJugador/arriba2.png");
        animacion->agregarFrame("Nivel2/FantasmaJugador/arriba3.png");
    }
}

sf::Vector2f FantasmaJugador::getPosicion() const {
    return sprite.getPosition();
}

sf::Vector2f FantasmaJugador::getDireccion() const {
    return direccion;
}

void FantasmaJugador::actualizarAnimacion(float deltaTime) {
    animacion->actualizar(deltaTime);
}