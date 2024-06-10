#include "FantasmaRojo.h"
#include <iostream>

FantasmaRojo::FantasmaRojo(float x, float y, float velocidad)
    : velocidad(velocidad), direccion(0, 0), vidas(42), posicionInicial(x, y) { // Inicializa la posición inicial
    animacion = new Animacion(0.1f);  // Tiempo entre frames
    animacion->agregarFrame("Nivel1/Fantasmas/Rojo/derecha1.png");
    animacion->agregarFrame("Nivel1/Fantasmas/Rojo/derecha2.png");
    animacion->agregarFrame("Nivel1/Fantasmas/Rojo/derecha3.png");

    sprite.setPosition(755, 480); //FANTASMA ROJO
    sprite.setScale(0.8f, 0.8f);
}

int FantasmaRojo::getVidas() const {
    return vidas;
}

void FantasmaRojo::dibujarVidas(sf::RenderWindow& ventana) {
    sf::Font font;
    if (!font.loadFromFile("Nivel1/fuentenivel1.ttf")) {

    }
    sf::Text textoVidas;
    textoVidas.setFont(font);
    textoVidas.setString(std::to_string(vidas));
    textoVidas.setCharacterSize(40);
    textoVidas.setFillColor(sf::Color::White);
    textoVidas.setPosition(190, 825);

    ventana.draw(textoVidas);
}

void FantasmaRojo::reducirVida() {
    vidas--;
}

void FantasmaRojo::setPosicionInicial() {
    sprite.setPosition(750, 480);
}

sf::Sprite& FantasmaRojo::getSprite() {
    return sprite;
}

void FantasmaRojo::cambiarTexturaPorPoder() {
    // Cambiar la textura del FantasmaRojo cuando el Jugador consume un poder
    animacion->limpiarFrames();
    animacion->agregarFrame("Nivel1/Fantasmas/perseguido1.png");
    animacion->agregarFrame("Nivel1/Fantasmas/perseguido2.png");
    animacion->agregarFrame("Nivel1/Fantasmas/perseguido3.png");
    // Puedes agregar más lógica aquí si necesitas hacer alguna acción especial cuando se active el poder
}//vas a caerrr animaciones DIOS, DAME FUERZAS

void FantasmaRojo::mostrarVentanaGanador(sf::RenderWindow& mainWindow, int ganador) {
    Ganador ventanaGanador(mainWindow, ganador);
    int opcion = ventanaGanador.mostrar();

}

bool FantasmaRojo::posicionValida(sf::Vector2f nuevaPosicion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
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


void FantasmaRojo::mover(sf::Vector2f direccion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
    sf::Vector2f nuevaPosicion = sprite.getPosition() + direccion * velocidad;

    if (posicionValida(nuevaPosicion, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
        sprite.setPosition(nuevaPosicion);
    }
}

void FantasmaRojo::dibujar(sf::RenderWindow& ventana) {
    animacion->aplicarA(sprite);
    ventana.draw(sprite);
}

void FantasmaRojo::setDireccion(sf::Vector2f nuevaDireccion) {
    direccion = nuevaDireccion;
    // Cambiar animaciones basadas en la dirección
    delete animacion;
    animacion = new Animacion(0.1f);  // Tiempo entre frames

    if (direccion.x > 0) {
        animacion->agregarFrame("Nivel1/Fantasmas/Rojo/derecha1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rojo/derecha2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rojo/derecha3.png");
    }
    else if (direccion.x < 0) {
        animacion->agregarFrame("Nivel1/Fantasmas/Rojo/izquierda1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rojo/izquierda2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rojo/izquierda3.png");
    }
    else if (direccion.y > 0) {
        animacion->agregarFrame("Nivel1/Fantasmas/Rojo/abajo1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rojo/abajo2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rojo/abajo3.png");
    }
    else if (direccion.y < 0) {
        animacion->agregarFrame("Nivel1/Fantasmas/Rojo/arriba1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rojo/arriba2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rojo/arriba3.png");
    }
}

sf::Vector2f FantasmaRojo::getPosicion() const {
    return sprite.getPosition();
}

sf::Vector2f FantasmaRojo::getDireccion() const {
    return direccion;
}

void FantasmaRojo::actualizarAnimacion(float deltaTime) {
    animacion->actualizar(deltaTime);
}
