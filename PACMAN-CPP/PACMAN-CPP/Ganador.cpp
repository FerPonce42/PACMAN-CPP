#include "Ganador.h"

Ganador::Ganador(sf::RenderWindow& mainWindow, int ganador)
    : window(mainWindow), selectedItemIndex(0) {
    if (!font.loadFromFile("Ganador/fuenteganador.ttf")) {
        // Manejo del error al cargar la fuente
    }

    // Cargar las texturas de fondo seg�n el ganador
    cargarTexturas(ganador);

    // Configuraci�n del texto de ganador
    textoGanador.setFont(font);
    textoGanador.setCharacterSize(80);
    textoGanador.setString("GANA EL JUGADOR " + std::to_string(ganador));
    textoGanador.setFillColor(sf::Color::Yellow);
    sf::FloatRect textBounds = textoGanador.getLocalBounds();
    textoGanador.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
    // Ajustar la posici�n en X para mover a la derecha
    textoGanador.setPosition(static_cast<float>(window.getSize().x) / 2.0f + 300.0f,
        static_cast<float>(window.getSize().y) / 4.0f);

    // Configuraci�n de la opci�n de reiniciar
    reiniciarTexto.setFont(font);
    reiniciarTexto.setCharacterSize(40);
    reiniciarTexto.setString("Reiniciar Partida");
    // Ajustar la posici�n en X para mover a la derecha
    reiniciarTexto.setPosition(static_cast<float>(window.getSize().x) / 2.0f - 20.0f,
        static_cast<float>(window.getSize().y) / 2.0f - 25.0f);
    reiniciarTexto.setFillColor(sf::Color::Cyan);  // Reiniciar seleccionado inicialmente

    // Configuraci�n de la opci�n de siguiente nivel
    siguienteNivelTexto.setFont(font);
    siguienteNivelTexto.setCharacterSize(40);
    siguienteNivelTexto.setString("Siguiente Nivel");
    // Ajustar la posici�n en X para mover a la derecha
    siguienteNivelTexto.setPosition(static_cast<float>(window.getSize().x) / 2.0f - 20.0f,
        static_cast<float>(window.getSize().y) / 2.0f + 25.0f);

    // Configuraci�n de la opci�n de salir
    salirTexto.setFont(font);
    salirTexto.setCharacterSize(40);
    salirTexto.setString("Salir");
    // Ajustar la posici�n en X para mover a la derecha
    salirTexto.setPosition(static_cast<float>(window.getSize().x) / 2.0f - 20.0f,
        static_cast<float>(window.getSize().y) / 2.0f + 75.0f);
}

void Ganador::cargarTexturas(int ganador) {
    if (ganador == 1) {
        if (!textureJugador1.loadFromFile("Ganador/Jugador1GANADOR.png")) {
            // Manejo del error al cargar la textura para jugador 1
        }
        fondoSprite.setTexture(textureJugador1);
    }
    else if (ganador == 2) {
        if (!textureJugador2.loadFromFile("Ganador/Jugador2GANADOR.png")) {
            // Manejo del error al cargar la textura para jugador 2
        }
        fondoSprite.setTexture(textureJugador2);
    }

    // Ajusta el tama�o del sprite para que cubra toda la ventana
    fondoSprite.setScale(window.getSize().x / fondoSprite.getLocalBounds().width,
        window.getSize().y / fondoSprite.getLocalBounds().height);
}

int Ganador::mostrar() {
    selectedItemIndex = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Up) {
                    MoveUp();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    MoveDown();
                }
                else if (event.key.code == sf::Keyboard::Return) {
                    return getSelectedOption();
                }
            }
        }

        window.clear();
        // Dibuja el fondo primero
        window.draw(fondoSprite);
        // Luego dibuja los textos y opciones
        window.draw(textoGanador);
        window.draw(reiniciarTexto);
        window.draw(siguienteNivelTexto);
        window.draw(salirTexto);
        window.display();
    }

    return 0;
}

void Ganador::MoveUp() {
    if (selectedItemIndex > 0) {
        reiniciarTexto.setFillColor(sf::Color::White);
        siguienteNivelTexto.setFillColor(sf::Color::White);
        salirTexto.setFillColor(sf::Color::White);
        selectedItemIndex--;
        if (selectedItemIndex == 0) {
            reiniciarTexto.setFillColor(sf::Color::Cyan);
        }
        else if (selectedItemIndex == 1) {
            siguienteNivelTexto.setFillColor(sf::Color::Cyan);
        }
        else {
            salirTexto.setFillColor(sf::Color::Cyan);
        }
    }
}

void Ganador::MoveDown() {
    if (selectedItemIndex < 2) {
        reiniciarTexto.setFillColor(sf::Color::White);
        siguienteNivelTexto.setFillColor(sf::Color::White);
        salirTexto.setFillColor(sf::Color::White);
        selectedItemIndex++;
        if (selectedItemIndex == 0) {
            reiniciarTexto.setFillColor(sf::Color::Cyan);
        }
        else if (selectedItemIndex == 1) {
            siguienteNivelTexto.setFillColor(sf::Color::Cyan);
        }
        else {
            salirTexto.setFillColor(sf::Color::Cyan);
        }
    }
}

int Ganador::getSelectedOption() {
    return selectedItemIndex;
}