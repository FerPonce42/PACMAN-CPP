#include "Creditos.h"
#include <iostream>

Creditos::Creditos(sf::RenderWindow& mainWindow) : window(mainWindow), returnToMenu(false) {
    
    if (!backgroundTexture.loadFromFile("Creditos/creditos.png")) {
        
    }
    backgroundSprite.setTexture(backgroundTexture);

  
    if (!font.loadFromFile("Creditos/fuentecreditos.ttf")) {
       
    }

   
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
        window.draw(backgroundSprite);  
        window.draw(regresarTexto);     
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
