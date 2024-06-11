#include "FantasmaRojo.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

FantasmaRojo::FantasmaRojo(float x, float y, float velocidad)
    : velocidad(velocidad), direccion(0, 0), direccionActual(1, 0), vidas(42), posicionInicial(x, y), poderActivo(false) {
    animacion = new Animacion(0.1f);  // Tiempo entre frames
    animacion->agregarFrame("Nivel1/Fantasmas/Rojo/derecha1.png");
    animacion->agregarFrame("Nivel1/Fantasmas/Rojo/derecha2.png");
    animacion->agregarFrame("Nivel1/Fantasmas/Rojo/derecha3.png");

    sprite.setPosition(755, 480); //FANTASMA ROJO
    sprite.setScale(0.8f, 0.8f);
    srand(static_cast<unsigned>(time(0)));
}

int FantasmaRojo::getVidas() const {
    return vidas;
}

void FantasmaRojo::dibujarVidas(sf::RenderWindow& ventana) {
    sf::Font font;
    if (!font.loadFromFile("Nivel1/fuentenivel1.ttf")) {
        // Manejo de errores
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
}

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

void FantasmaRojo::moverAI(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio, sf::Vector2f playerPosition, bool powerActive) {
    if (powerActive && !poderActivo) {
        poderActivo = true;
        cambiarTexturaPorPoder();
    }
    else if (!powerActive && poderActivo) {
        poderActivo = false;
        // Reset animation to default
        animacion->limpiarFrames();
        animacion->agregarFrame("Nivel1/Fantasmas/Rojo/derecha1.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rojo/derecha2.png");
        animacion->agregarFrame("Nivel1/Fantasmas/Rojo/derecha3.png");
    }

    if (poderActivo) {
        avoidPlayer(playerPosition, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
    }
    else {
        chasePlayer(playerPosition, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
    }

    mover(direccionActual, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio);
}

void FantasmaRojo::avoidPlayer(sf::Vector2f playerPosition, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
    sf::Vector2f currentPosition = getPosicion();
    if (std::hypot(currentPosition.x - playerPosition.x, currentPosition.y - playerPosition.y) < 150) {
        if (playerPosition.x < currentPosition.x && posicionValida({ currentPosition.x + velocidad, currentPosition.y }, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
            direccionActual = { 1, 0 };
        }
        else if (playerPosition.x > currentPosition.x && posicionValida({ currentPosition.x - velocidad, currentPosition.y }, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
            direccionActual = { -1, 0 };
        }

        if (playerPosition.y < currentPosition.y && posicionValida({ currentPosition.x, currentPosition.y + velocidad }, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
            direccionActual = { 0, 1 };
        }
        else if (playerPosition.y > currentPosition.y && posicionValida({ currentPosition.x, currentPosition.y - velocidad }, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
            direccionActual = { 0, -1 };
        }
    }
}

void FantasmaRojo::chasePlayer(sf::Vector2f playerPosition, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
    sf::Vector2f currentPosition = getPosicion();
    if (std::hypot(currentPosition.x - playerPosition.x, currentPosition.y - playerPosition.y) > 150) {
        if (playerPosition.x < currentPosition.x && posicionValida({ currentPosition.x - velocidad, currentPosition.y }, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
            direccionActual = { -1, 0 };
        }
        else if (playerPosition.x > currentPosition.x && posicionValida({ currentPosition.x + velocidad, currentPosition.y }, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
            direccionActual = { 1, 0 };
        }

        if (playerPosition.y < currentPosition.y && posicionValida({ currentPosition.x, currentPosition.y - velocidad }, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
            direccionActual = { 0, -1 };
        }
        else if (playerPosition.y > currentPosition.y && posicionValida({ currentPosition.x, currentPosition.y + velocidad }, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
            direccionActual = { 0, 1 };
        }
    }
}

void FantasmaRojo::seleccionarNuevaDireccion(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
    std::vector<sf::Vector2f> direccionesValidas;

    sf::Vector2f posiblesDirecciones[] = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    for (auto& dir : posiblesDirecciones) {
        sf::Vector2f nuevaPosicion = sprite.getPosition() + dir * velocidad;
        if (posicionValida(nuevaPosicion, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio) &&
            (mapa[static_cast<int>((nuevaPosicion.y - posYInicio) / altoCelda)][static_cast<int>((nuevaPosicion.x - posXInicio) / anchoCelda)] == 0 ||
                direccionActual != -dir)) {
            direccionesValidas.push_back(dir);
        }
    }

    if (!direccionesValidas.empty()) {
        int indiceAleatorio = rand() % direccionesValidas.size();
        direccionActual = direccionesValidas[indiceAleatorio];
    }

    // Actualizar la animación basada en la dirección seleccionada
    setDireccion(direccionActual);
}

void FantasmaRojo::dibujar(sf::RenderWindow& ventana) {
    animacion->aplicarA(sprite);
    ventana.draw(sprite);
}

void FantasmaRojo::setDireccion(sf::Vector2f nuevaDireccion) {
    direccion = nuevaDireccion;

    // Actualizar los frames de la animación basándose en la dirección
    animacion->limpiarFrames(); // Limpiar todos los frames actuales

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

