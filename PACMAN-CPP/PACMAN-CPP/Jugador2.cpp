#include "Jugador2.h"
#include <iostream>

Jugador2::Jugador2(float x, float y, float velocidad)
    : velocidad(velocidad), direccion(0, 0), vidas(3), posicionInicial(x, y) { // Inicializa la posición inicial
    animacion = new Animacion(0.1f);  // Tiempo entre frames
    animacion->agregarFrame("Nivel3/Jugador2/derecha1.png");
    animacion->agregarFrame("Nivel3/Jugador2/derecha2.png");
    animacion->agregarFrame("Nivel3/Jugador2/derecha3.png");

    sprite.setPosition(1140, 550); //JUGADOR 2 PACMAN
    sprite.setScale(0.8f, 0.8f);
}

int Jugador2::getVidas() const {
    return vidas;
}

void Jugador2::dibujarVidas(sf::RenderWindow& ventana) {
    sf::Font font;
    if (!font.loadFromFile("Nivel3/fuentenivel3.ttf")) {
        
    }
    sf::Text textoVidas;
    textoVidas.setFont(font);
    textoVidas.setString(std::to_string(vidas));
    textoVidas.setCharacterSize(40);
    textoVidas.setFillColor(sf::Color::White);
    textoVidas.setPosition(200, 900);

    ventana.draw(textoVidas);
}

void Jugador2::reducirVida() {
    vidas--;
}

void Jugador2::setPosicionInicial() {
    sprite.setPosition(1150, 550);
}

sf::Sprite& Jugador2::getSprite() {
    return sprite;
}

void Jugador2::mostrarVentanaGanador(sf::RenderWindow& mainWindow, int ganador) {
    Ganador ventanaGanador(mainWindow, ganador);
    int opcion = ventanaGanador.mostrar();

}

bool Jugador2::posicionValida(sf::Vector2f nuevaPosicion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
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

        if (fila < 0 || fila >= altoMapa || columna < 0 || columna >= anchoMapa || mapa[fila][columna] != 0) {
            return false;
        }
    }

    return true;
}

void Jugador2::mover(sf::Vector2f direccion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
    sf::Vector2f nuevaPosicion = sprite.getPosition() + direccion * velocidad;

    if (posicionValida(nuevaPosicion, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
        sprite.setPosition(nuevaPosicion);
    }
}

void Jugador2::dibujar(sf::RenderWindow& ventana) {
    animacion->aplicarA(sprite);
    ventana.draw(sprite);
}

void Jugador2::setDireccion(sf::Vector2f nuevaDireccion) {
    direccion = nuevaDireccion;
    // Cambiar animaciones basadas en la dirección
    delete animacion;
    animacion = new Animacion(0.1f);  // Tiempo entre frames

    if (direccion.x > 0) {
        animacion->agregarFrame("Nivel3/Jugador2/derecha1.png");
        animacion->agregarFrame("Nivel3/Jugador2/derecha2.png");
        animacion->agregarFrame("Nivel3/Jugador2/derecha3.png");
    }
    else if (direccion.x < 0) {
        animacion->agregarFrame("Nivel3/Jugador2/izquierda1.png");
        animacion->agregarFrame("Nivel3/Jugador2/izquierda2.png");
        animacion->agregarFrame("Nivel3/Jugador2/izquierda3.png");
    }
    else if (direccion.y > 0) {
        animacion->agregarFrame("Nivel3/Jugador2/abajo1.png");
        animacion->agregarFrame("Nivel3/Jugador2/abajo2.png");
        animacion->agregarFrame("Nivel3/Jugador2/abajo3.png");
    }
    else if (direccion.y < 0) {
        animacion->agregarFrame("Nivel3/Jugador2/arriba1.png");
        animacion->agregarFrame("Nivel3/Jugador2/arriba2.png");
        animacion->agregarFrame("Nivel3/Jugador2/arriba3.png");
    }
}

sf::Vector2f Jugador2::getPosicion() const {
    return sprite.getPosition();
}

sf::Vector2f Jugador2::getDireccion() const {
    return direccion;
}

void Jugador2::actualizarAnimacion(float deltaTime) {
    animacion->actualizar(deltaTime);
}
