#include "MenuPrincipal.h"

MenuPrincipal::MenuPrincipal(float ancho, float alto) {
    if (!fuente.loadFromFile("TexturasParaMenuPrincipal/fuentemenuprincipal.ttf")) {
        
    }

    if (!texturaFondo.loadFromFile("TexturasParaMenuPrincipal/Fondo.png")) {
        
    }

    spriteFondo.setTexture(texturaFondo);
    spriteFondo.setScale(ancho / spriteFondo.getGlobalBounds().width, alto / spriteFondo.getGlobalBounds().height);

    textoMenu[0].setFont(fuente);
    textoMenu[0].setFillColor(sf::Color::Yellow);
    textoMenu[0].setString("PACMAN-CPP");
    textoMenu[0].setCharacterSize(120);
    // Calcular la posición X centrada
    float textoX = (ancho - textoMenu[0].getGlobalBounds().width) / 2;
    textoMenu[0].setPosition(sf::Vector2f(textoX, alto / 5));
    // Desplazamiento adicional hacia la derecha
    float offsetX = 290;

    // Resto de los textos
    textoMenu[1].setFont(fuente);
    textoMenu[1].setFillColor(sf::Color::Cyan);
    textoMenu[1].setString("Jugar");
    textoMenu[1].setCharacterSize(40);
    textoMenu[1].setPosition(sf::Vector2f(textoX + offsetX, alto / 2 - 100));

    textoMenu[2].setFont(fuente);
    textoMenu[2].setFillColor(sf::Color::White);
    textoMenu[2].setString("Opciones");
    textoMenu[2].setCharacterSize(40);
    textoMenu[2].setPosition(sf::Vector2f(textoX + offsetX, alto / 2 - 50));

    textoMenu[3].setFont(fuente);
    textoMenu[3].setFillColor(sf::Color::White);
    textoMenu[3].setString("Creditos");
    textoMenu[3].setCharacterSize(40);
    textoMenu[3].setPosition(sf::Vector2f(textoX + offsetX, alto / 2));

    textoMenu[4].setFont(fuente);
    textoMenu[4].setFillColor(sf::Color::White);
    textoMenu[4].setString("Salir");
    textoMenu[4].setCharacterSize(40);
    textoMenu[4].setPosition(sf::Vector2f(textoX + offsetX, alto / 2 + 50));

    indiceItemSeleccionado = 1; 
}

void MenuPrincipal::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(spriteFondo);

    for (int i = 0; i < 5; i++) {
        ventana.draw(textoMenu[i]);
    }
}

void MenuPrincipal::moverArriba() {
    if (indiceItemSeleccionado > 1) {
        textoMenu[indiceItemSeleccionado].setFillColor(sf::Color::White);
        indiceItemSeleccionado--;
        textoMenu[indiceItemSeleccionado].setFillColor(sf::Color::Cyan);
    }
    else if (indiceItemSeleccionado == 1) {
        textoMenu[indiceItemSeleccionado].setFillColor(sf::Color::White);
        indiceItemSeleccionado = 4; // Avanza a la última opción ("SALIR")
        textoMenu[indiceItemSeleccionado].setFillColor(sf::Color::Cyan);
    }
}

void MenuPrincipal::moverAbajo() {
    if (indiceItemSeleccionado < 4) { // Ajusta el número al total de opciones menos 1
        textoMenu[indiceItemSeleccionado].setFillColor(sf::Color::White);
        indiceItemSeleccionado++;
        textoMenu[indiceItemSeleccionado].setFillColor(sf::Color::Cyan);
    }
    else if (indiceItemSeleccionado == 4) { // Ajusta el número al total de opciones menos 1
        textoMenu[indiceItemSeleccionado].setFillColor(sf::Color::White);
        indiceItemSeleccionado = 1; // Retrocede a la segunda opción ("JUGAR")
        textoMenu[indiceItemSeleccionado].setFillColor(sf::Color::Cyan);
    }
}

int MenuPrincipal::obtenerOpcionSeleccionada() {
    return indiceItemSeleccionado;
}