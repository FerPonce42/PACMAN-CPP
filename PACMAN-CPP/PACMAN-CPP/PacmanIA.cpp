#include "PacmanIA.h"
#include <iostream>

PacmanIA::PacmanIA(float x, float y, float velocidad)
    : velocidad(velocidad), direccion(0, 0), vidas(3), posicionInicial(x, y), puntaje(0) { // Inicializa la posición inicial
    animacion = new Animacion(0.1f);  // Tiempo entre frames
    animacion->agregarFrame("Nivel2/PacmanIA/derecha1.png");
    animacion->agregarFrame("Nivel2/PacmanIA/derecha2.png");
    animacion->agregarFrame("Nivel2/PacmanIA/derecha3.png");

    sprite.setPosition(630, 560); //PACMAN CONTROLADO POR IA
    sprite.setScale(0.8f, 0.8f);
}

void PacmanIA::aumentarPuntaje(int puntos) {
    puntaje += puntos;
}

int PacmanIA::getPuntaje() const {
    return puntaje;
}

int PacmanIA::getVidas() const {
    return vidas;
}

void PacmanIA::dibujarVidas(sf::RenderWindow& ventana) {
    sf::Font font;
    if (!font.loadFromFile("Nivel2/fuentenivel2.ttf")) {

    }
    sf::Text textoVidas;
    textoVidas.setFont(font);
    textoVidas.setString(std::to_string(vidas));
    textoVidas.setCharacterSize(40);
    textoVidas.setFillColor(sf::Color::White);
    textoVidas.setPosition(200, 900);

    ventana.draw(textoVidas);
}

void PacmanIA::reducirVida() {
    vidas--;
}

void PacmanIA::setPosicionInicial() {
    sprite.setPosition(630, 560);
}

sf::Sprite& PacmanIA::getSprite() {
    return sprite;
}

void PacmanIA::mostrarVentanaGanador(sf::RenderWindow& mainWindow, int ganador) {
    Ganador ventanaGanador(mainWindow, ganador);
    int opcion = ventanaGanador.mostrar();
}

void PacmanIA::dibujarPuntaje(sf::RenderWindow& ventana) {
    sf::Font font;
    if (!font.loadFromFile("Nivel2/fuentenivel2.ttf")) {
        // Manejo de errores
    }
    sf::Text textoPuntaje;
    textoPuntaje.setFont(font);
    textoPuntaje.setString(std::to_string(puntaje));
    textoPuntaje.setCharacterSize(50);
    textoPuntaje.setFillColor(sf::Color::White);
    textoPuntaje.setPosition(250, 85); // Ajusta la posición según tus necesidades

    ventana.draw(textoPuntaje);
}

bool PacmanIA::posicionValida(sf::Vector2f nuevaPosicion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
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

void PacmanIA::mover(sf::Vector2f direccion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
    sf::Vector2f nuevaPosicion = sprite.getPosition() + direccion * velocidad;

    if (posicionValida(nuevaPosicion, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
        sprite.setPosition(nuevaPosicion);
    }
}

void PacmanIA::dibujar(sf::RenderWindow& ventana) {
    animacion->aplicarA(sprite);
    ventana.draw(sprite);
}

void PacmanIA::setDireccion(sf::Vector2f nuevaDireccion) {
    direccion = nuevaDireccion;
    // Cambiar animaciones basadas en la dirección
    delete animacion;
    animacion = new Animacion(0.1f);  // Tiempo entre frames

    if (direccion.x > 0) {
        animacion->agregarFrame("Nivel2/PacmanIA/derecha1.png");
        animacion->agregarFrame("Nivel2/PacmanIA/derecha2.png");
        animacion->agregarFrame("Nivel2/PacmanIA/derecha3.png");
    }
    else if (direccion.x < 0) {
        animacion->agregarFrame("Nivel2/PacmanIA/izquierda1.png");
        animacion->agregarFrame("Nivel2/PacmanIA/izquierda2.png");
        animacion->agregarFrame("Nivel2/PacmanIA/izquierda3.png");
    }
    else if (direccion.y > 0) {
        animacion->agregarFrame("Nivel2/PacmanIA/abajo1.png");
        animacion->agregarFrame("Nivel2/PacmanIA/abajo2.png");
        animacion->agregarFrame("Nivel2/PacmanIA/abajo3.png");
    }
    else if (direccion.y < 0) {
        animacion->agregarFrame("Nivel2/PacmanIA/arriba1.png");
        animacion->agregarFrame("Nivel2/PacmanIA/arriba2.png");
        animacion->agregarFrame("Nivel2/PacmanIA/arriba3.png");
    }
}

sf::Vector2f PacmanIA::getPosicion() const {
    return sprite.getPosition();
}

sf::Vector2f PacmanIA::getDireccion() const {
    return direccion;
}

void PacmanIA::actualizarAnimacion(float deltaTime) {
    animacion->actualizar(deltaTime);
}