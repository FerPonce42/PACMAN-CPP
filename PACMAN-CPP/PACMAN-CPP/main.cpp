#include <SFML/Graphics.hpp>
#include "MenuPrincipal.h"
#include "SeleccionNiveles.h"
#include "Musica.h"
#include "Nivel1.h"
#include "Nivel2.h" // Agregamos la inclusión del header para el nivel 2

int main() {
    sf::RenderWindow ventana(sf::VideoMode(1920, 1080), "PACMAN-CPP");

    MenuPrincipal menu(ventana.getSize().x, ventana.getSize().y);
    SeleccionNiveles menuNiveles(ventana.getSize().x, ventana.getSize().y);
    Nivel1 nivel1(ventana, ventana.getSize().x, ventana.getSize().y);
    Nivel2 nivel2(ventana, ventana.getSize().x, ventana.getSize().y); // Creamos un objeto para el nivel 2

    Musica musica;
    musica.cargarMusicaMenu();
    musica.setVolume(50);
    musica.setLoop(true);
    musica.reproducir();

    bool enMenu = true;
    bool enMenuNiveles = false;
    bool enNivel1 = false;
    bool enNivel2 = false; // Agregamos una variable para el nivel 2

    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }

            if (enNivel1) {
                nivel1.manejarEventos();
            }
            else if (enNivel2) { // Manejamos eventos para el nivel 2 si estamos en él
                nivel2.manejarEventos();
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
                            enNivel1 = false;
                            enNivel2 = false; // Aseguramos que no estemos en el nivel 2
                        }
                        else if (opcionSeleccionada == 4) {
                            ventana.close();
                        }
                    }
                    else if (enMenuNiveles) {
                        if (menuNiveles.obtenerNivelSeleccionado() == 4) {
                            enMenu = true;
                            enMenuNiveles = false;
                            enNivel1 = false;
                            enNivel2 = false; // Aseguramos que no estemos en el nivel 2
                        }
                        else if (menuNiveles.obtenerNivelSeleccionado() == 1) {
                            enMenuNiveles = false;
                            enNivel1 = true;
                            enNivel2 = false; // Aseguramos que no estemos en el nivel 2
                            musica.detener();
                            musica.cargarMusicaNivel1();
                            musica.setLoop(true);
                            musica.reproducir();
                        }
                        else if (menuNiveles.obtenerNivelSeleccionado() == 2) {
                            enMenuNiveles = false;
                            enNivel1 = false;
                            enNivel2 = true; // Cambiamos a true cuando seleccionamos el nivel 2
                            musica.detener();
                            musica.cargarMusicaNivel2(); // Cargamos la música del nivel 2
                            musica.setLoop(true);
                            musica.reproducir(); // Reproducimos la música del nivel 2
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

        if (enNivel1) {
            nivel1.mostrar();
            nivel1.actualizar();
        }
        else if (enNivel2) { // Mostramos y actualizamos el nivel 2 si estamos en él
            nivel2.mostrar();
            nivel2.actualizar();
        }

        ventana.display();
    }

    return 0;
}
