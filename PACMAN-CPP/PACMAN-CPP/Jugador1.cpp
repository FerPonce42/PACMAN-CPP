#include "Jugador1.h"
#include <iostream>

Jugador1::Jugador1(float x, float y, float velocidad)
    : velocidad(velocidad), direccion(0, 0), vidas(3), posicionInicial(x, y) { // Inicializa la posición inicial
    animacion = new Animacion(0.1f);  // Tiempo entre frames
    animacion->agregarFrame("Nivel3/Jugador1/derecha1.png");
    animacion->agregarFrame("Nivel3/Jugador1/derecha2.png");
    animacion->agregarFrame("Nivel3/Jugador1/derecha3.png");

    sprite.setPosition(860, 510); //JUGADOR 1 FANTASMA
    sprite.setScale(0.8f, 0.8f);
}

int Jugador1::getVidas() const {
    return vidas;
}

void Jugador1::dibujarVidas(sf::RenderWindow& ventana) {
    sf::Font font;
    if (!font.loadFromFile("Nivel3/fuentenivel3.ttf")) {
        
    }
    sf::Text textoVidas;
    textoVidas.setFont(font);
    textoVidas.setString(std::to_string(vidas));
    textoVidas.setCharacterSize(40);
    textoVidas.setFillColor(sf::Color::White);
    textoVidas.setPosition(190, 825);

    ventana.draw(textoVidas);
}

void Jugador1::reducirVida() {
    vidas--;
}

void Jugador1::setPosicionInicial() {
    sprite.setPosition(860, 510);
}

sf::Sprite& Jugador1::getSprite() {
    return sprite;
}

void Jugador1::cambiarTexturaPorPoder() {
    // Cambiar la textura del jugador 1 cuando el jugador 2 consume un poder
    animacion->limpiarFrames();
    animacion->agregarFrame("Nivel3/Jugador1/perseguido1.png");
    animacion->agregarFrame("Nivel3/Jugador1/perseguido2.png");
    animacion->agregarFrame("Nivel3/Jugador1/perseguido3.png");
    // Puedes agregar más lógica aquí si necesitas hacer alguna acción especial cuando se active el poder
}//vas a caerrr animaciones DIOS, DAME FUERZAS

void Jugador1::mostrarVentanaGanador(sf::RenderWindow& mainWindow, int ganador) {
    Ganador ventanaGanador(mainWindow, ganador);
    int opcion = ventanaGanador.mostrar();

}

bool Jugador1::posicionValida(sf::Vector2f nuevaPosicion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
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


void Jugador1::mover(sf::Vector2f direccion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
    sf::Vector2f nuevaPosicion = sprite.getPosition() + direccion * velocidad;

    if (posicionValida(nuevaPosicion, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
        sprite.setPosition(nuevaPosicion);
    }
}

void Jugador1::dibujar(sf::RenderWindow& ventana) {
    animacion->aplicarA(sprite);
    ventana.draw(sprite);
}

void Jugador1::setDireccion(sf::Vector2f nuevaDireccion) {
    direccion = nuevaDireccion;
    // Cambiar animaciones basadas en la direcci�n
    delete animacion;
    animacion = new Animacion(0.1f);  // Tiempo entre frames

    if (direccion.x > 0) {
        animacion->agregarFrame("Nivel3/Jugador1/derecha1.png");
        animacion->agregarFrame("Nivel3/Jugador1/derecha2.png");
        animacion->agregarFrame("Nivel3/Jugador1/derecha3.png");
    }
    else if (direccion.x < 0) {
        animacion->agregarFrame("Nivel3/Jugador1/izquierda1.png");
        animacion->agregarFrame("Nivel3/Jugador1/izquierda2.png");
        animacion->agregarFrame("Nivel3/Jugador1/izquierda3.png");
    }
    else if (direccion.y > 0) {
        animacion->agregarFrame("Nivel3/Jugador1/abajo1.png");
        animacion->agregarFrame("Nivel3/Jugador1/abajo2.png");
        animacion->agregarFrame("Nivel3/Jugador1/abajo3.png");
    }
    else if (direccion.y < 0) {
        animacion->agregarFrame("Nivel3/Jugador1/arriba1.png");
        animacion->agregarFrame("Nivel3/Jugador1/arriba2.png");
        animacion->agregarFrame("Nivel3/Jugador1/arriba3.png");
    }
}

sf::Vector2f Jugador1::getPosicion() const {
    return sprite.getPosition();
}

sf::Vector2f Jugador1::getDireccion() const {
    return direccion;
}

void Jugador1::actualizarAnimacion(float deltaTime) {
    animacion->actualizar(deltaTime);
}