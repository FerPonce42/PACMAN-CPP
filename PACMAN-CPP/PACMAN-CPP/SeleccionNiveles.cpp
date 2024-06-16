#include "SeleccionNiveles.h"
#include <iostream>

SeleccionNiveles::SeleccionNiveles(float ancho, float alto) {
    if (!fuente.loadFromFile("TexturasParaMenuPrincipal/fuentemenuprincipal.ttf")) {
        
    }

    
    if (!texturaFondo.loadFromFile("TexturasParaMenuPrincipal/Fondo.png")) {
        
    }

    spriteFondo.setTexture(texturaFondo);
    spriteFondo.setScale(ancho / spriteFondo.getGlobalBounds().width, alto / spriteFondo.getGlobalBounds().height);

    textoNivel[0].setFont(fuente);
    textoNivel[0].setFillColor(sf::Color::Green);
    textoNivel[0].setString("Modos de Juego");
    textoNivel[0].setCharacterSize(80);
    textoNivel[0].setPosition(sf::Vector2f(640, 200));
                                         
    textoNivel[1].setFont(fuente);
    textoNivel[1].setFillColor(sf::Color::White);
    textoNivel[1].setString("1. Clasico");
    textoNivel[1].setCharacterSize(40);
    textoNivel[1].setPosition(sf::Vector2f(800, 350));

    textoNivel[2].setFont(fuente);
    textoNivel[2].setFillColor(sf::Color::White);
    textoNivel[2].setString("2. Invertido");
    textoNivel[2].setCharacterSize(40);
    textoNivel[2].setPosition(sf::Vector2f(800, 450));

    textoNivel[3].setFont(fuente);
    textoNivel[3].setFillColor(sf::Color::White);
    textoNivel[3].setString("3. Versus");
    textoNivel[3].setCharacterSize(40);
    textoNivel[3].setPosition(sf::Vector2f(800, 550));

    textoNivel[4].setFont(fuente);
    textoNivel[4].setFillColor(sf::Color::White);
    textoNivel[4].setString("<- Retroceder");
    textoNivel[4].setCharacterSize(30);
    
    textoNivel[4].setPosition(sf::Vector2f(ancho - 480, alto - 360));

    indiceNivelSeleccionado = 1; 
    textoNivel[indiceNivelSeleccionado].setFillColor(sf::Color::Cyan); 
}

void SeleccionNiveles::dibujar(sf::RenderWindow& ventana) {
    
    ventana.draw(spriteFondo);

    for (int i = 0; i < 5; i++) {
        ventana.draw(textoNivel[i]);
    }
}

void SeleccionNiveles::moverArriba() {
    if (indiceNivelSeleccionado > 1) {
        textoNivel[indiceNivelSeleccionado].setFillColor(sf::Color::White);
        indiceNivelSeleccionado--;
        textoNivel[indiceNivelSeleccionado].setFillColor(sf::Color::Cyan);
    }
    else if (indiceNivelSeleccionado == 1) {
        textoNivel[indiceNivelSeleccionado].setFillColor(sf::Color::White);
        indiceNivelSeleccionado = 4;
        textoNivel[indiceNivelSeleccionado].setFillColor(sf::Color::Cyan);
    }
}

void SeleccionNiveles::moverAbajo() {
    if (indiceNivelSeleccionado < 4) {
        textoNivel[indiceNivelSeleccionado].setFillColor(sf::Color::White);
        indiceNivelSeleccionado++;
        textoNivel[indiceNivelSeleccionado].setFillColor(sf::Color::Cyan);
    }
    else if (indiceNivelSeleccionado == 4) {
        textoNivel[indiceNivelSeleccionado].setFillColor(sf::Color::White);
        indiceNivelSeleccionado = 1;
        textoNivel[indiceNivelSeleccionado].setFillColor(sf::Color::Cyan);
    }
}


int SeleccionNiveles::obtenerNivelSeleccionado() {
    return indiceNivelSeleccionado;
}

bool SeleccionNiveles::seSeleccionoRetroceder() {
    return indiceNivelSeleccionado == 4;
}