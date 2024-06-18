//PACMAN-CPP 2024-1 Ciencia de la Computacion UCSP
/*
Fernando Ponce
Maricielo Luna
Nicol Rocha
Fabricio Stelman
*/
#include <SFML/Graphics.hpp>
#include "MenuPrincipal.h"
#include "SeleccionNiveles.h"
#include "Musica.h"
#include "Nivel1.h"
#include "Nivel2.h"
#include "Nivel3.h"
#include "Pausa.h"
#include "Creditos.h"  

int main() {
    sf::RenderWindow ventana(sf::VideoMode(1920, 1080), "PACMAN-CPP");

    MenuPrincipal menu(ventana.getSize().x, ventana.getSize().y);
    SeleccionNiveles menuNiveles(ventana.getSize().x, ventana.getSize().y);
    Nivel1 nivel1(ventana, ventana.getSize().x, ventana.getSize().y);
    Nivel2 nivel2(ventana, ventana.getSize().x, ventana.getSize().y);
    Nivel3 nivel3(ventana, ventana.getSize().x, ventana.getSize().y);

    Pausa pausa(ventana); 
    Creditos creditos(ventana); 

    Musica musica;
    musica.cargarMusicaMenu();
    musica.setVolume(50);
    musica.setLoop(true);
    musica.reproducir();

    bool enMenu = true;
    bool enMenuNiveles = false;
    bool enNivel1 = false;
    bool enNivel2 = false;
    bool enNivel3 = false;
    bool enCreditos = false;  

    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }

            if (enNivel1) {
                nivel1.manejarEventos();
            }
            else if (enNivel2) {
                nivel2.manejarEventos();
            }
            else if (enNivel3) {
                nivel3.manejarEventos();
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
                            enNivel2 = false;
                            enNivel3 = false;
                        }
                        else if (opcionSeleccionada == 2) {  
                            enMenu = false;
                            enMenuNiveles = false;
                            enNivel1 = false;
                            enNivel2 = false;
                            enNivel3 = false;
                            enCreditos = true; 
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
                            enNivel2 = false;
                            enNivel3 = false;
                        }
                        else if (menuNiveles.obtenerNivelSeleccionado() == 1) {
                            enMenuNiveles = false;
                            enNivel1 = true;
                            enNivel2 = false;
                            enNivel3 = false;
                            musica.detener();
                            musica.cargarMusicaNivel1();
                            musica.setLoop(true);
                            musica.reproducir();
                        }
                        else if (menuNiveles.obtenerNivelSeleccionado() == 2) {
                            enMenuNiveles = false;
                            enNivel1 = false;
                            enNivel2 = true;
                            enNivel3 = false;
                            musica.detener();
                            musica.cargarMusicaNivel2();
                            musica.setLoop(true);
                            musica.reproducir();
                        }
                        else if (menuNiveles.obtenerNivelSeleccionado() == 3) {
                            enMenuNiveles = false;
                            enNivel1 = false;
                            enNivel2 = false;
                            enNivel3 = true;
                            musica.detener();
                            musica.cargarMusicaNivel3();
                            musica.setLoop(true);
                            musica.reproducir();
                        }
                    }

                }

                if (evento.key.code == sf::Keyboard::Space) {
                    if (enNivel1 || enNivel2 || enNivel3) {
                        int resultadoPausa = pausa.mostrar();
                        if (resultadoPausa == 1) {
                           
                            enMenu = true;
                            enMenuNiveles = false;
                            enNivel1 = false;
                            enNivel2 = false;
                            enNivel3 = false;
                            musica.detener();
                            musica.cargarMusicaMenu();
                            musica.setLoop(true);
                            musica.reproducir();
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
        else if (enCreditos) {
            creditos.mostrar();  
            if (creditos.shouldReturnToMenu()) {
                enCreditos = false;
                enMenu = true;
            }
        }

        if (enNivel1) {
            nivel1.mostrar();
            nivel1.actualizar();
        }
        else if (enNivel2) {
            nivel2.mostrar();
            nivel2.actualizar();
        }
        else if (enNivel3) {
            nivel3.mostrar();
            nivel3.actualizar();
        }

        ventana.display();
    }

    return 0;
}
