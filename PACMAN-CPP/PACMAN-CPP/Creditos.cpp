#include "Creditos.h"
#include <iostream>

Creditos::Creditos(sf::RenderWindow& mainWindow) : window(mainWindow), returnToMenu(false) {
    // Cargar la textura de fondo
    if (!backgroundTexture.loadFromFile("Creditos/creditos.png")) {
        // Manejo de errores si no se puede cargar la imagen.
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Cargar la fuente
    if (!font.loadFromFile("Creditos/fuentecreditos.ttf")) {
        // Manejo de errores si no se puede cargar la fuente.
    }

    // Configurar el texto del botón de regresar
    regresarTexto.setFont(font);
    regresarTexto.setString("Regresar al menu");
    regresarTexto.setCharacterSize(24);
    regresarTexto.setFillColor(sf::Color::White);
    regresarTexto.setPosition(sf::Vector2f(window.getSize().x / 2.0f - regresarTexto.getGlobalBounds().width / 2.0f, window.getSize().y - 50));
}

int Creditos::mostrar() {
    returnToMenu = false;

    while (window.isOpen() && !returnToMenu) {
        window.clear();
        window.draw(backgroundSprite);  // Dibujar la imagen de fondo
        window.draw(regresarTexto);     // Dibujar el texto de regresar
        window.display();

        handleInput();
    }

    return 0;
}

void Creditos::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::Return) {
                returnToMenu = true;
            }
        }
    }
}

bool Creditos::shouldReturnToMenu() {
    return returnToMenu;
}
