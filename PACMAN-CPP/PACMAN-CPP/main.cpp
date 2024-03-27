#include <SFML/Graphics.hpp>
#include "MenuPrincipal.h"
#include "SeleccionNiveles.h"
#include "MusicaMenu.h"

int main() {
    sf::RenderWindow ventana(sf::VideoMode(1920, 1080), "PACMAN-CPP");

    MenuPrincipal menu(ventana.getSize().x, ventana.getSize().y);
    SeleccionNiveles menuNiveles(ventana.getSize().x, ventana.getSize().y);

    Musica musica;
    musica.cargarMusica();
    musica.setVolume(50);
    musica.setLoop(true);
    musica.reproducir();

    bool enMenu = true;
    bool enMenuNiveles = false;

    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }

            if (evento.type == sf::Event::KeyReleased) {
                if (evento.key.code == sf::Keyboard::Up) {
                    if (enMenu) {
                        menu.moverArriba();
                    }
                    else if (enMenuNiveles) {
                        menuNiveles.moverArriba();
                    }
                }
                if (evento.key.code == sf::Keyboard::Down) {
                    if (enMenu) {
                        menu.moverAbajo();
                    }
                    else if (enMenuNiveles) {
                        menuNiveles.moverAbajo();
                    }
                }

                if (evento.key.code == sf::Keyboard::Return) {
                    if (enMenu) {
                        int opcionSeleccionada = menu.obtenerOpcionSeleccionada();
                        if (opcionSeleccionada == 1) {
                            enMenu = false;
                            enMenuNiveles = true;
                        }
                        else if (opcionSeleccionada == 4) {
                            ventana.close();
                        }
                    }
                    else if (enMenuNiveles) {
                        if (menuNiveles.obtenerNivelSeleccionado() == 4) {
                            enMenu = true;
                            enMenuNiveles = false;
                        }
                    }
                }
            }
        }

        ventana.clear();

        if (enMenu) {
            menu.dibujar(ventana);
        }
        else if (enMenuNiveles) {
            menuNiveles.dibujar(ventana);
        }

        ventana.display();
    }

    return 0;
}
