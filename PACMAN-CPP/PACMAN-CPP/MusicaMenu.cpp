#include "MusicaMenu.h"
#include <iostream>

Musica::Musica() {
    
}

void Musica::cargarMusica() {
    if (!musica.openFromFile("TexturasParaMenuPrincipal/musicamenu.mp3")) {
        std::cerr << "Error al cargar la m�sica." << std::endl;
    }
}

void Musica::reproducir() {
    musica.setLoop(true); // Establece la reproducci�n en bucle
    musica.play();
}

void Musica::detener() {
    musica.stop();
}

void Musica::pausar() {
    musica.pause();
}

void Musica::reanudar() {
    musica.play();
}

void Musica::setVolume(float volume) {
    musica.setVolume(volume);
}

void Musica::setLoop(bool loop) {
    musica.setLoop(loop);
}