#include "Musica.h"
#include <iostream>

Musica::Musica() {

}

void Musica::cargarMusicaMenu() {
    if (!musica.openFromFile("TexturasParaMenuPrincipal/musicamenu.mp3")) {
        std::cerr << "Error al cargar la música del menú." << std::endl;
    }
}

void Musica::cargarMusicaNivel1() {
    if (!musica.openFromFile("Nivel1/musicanivel1.mp3")) {
        std::cerr << "Error al cargar la música del nivel 1." << std::endl;
    }
}

void Musica::cargarMusicaNivel2() {
    if (!musica.openFromFile("Nivel2/musicanivel2.mp3")) {
        std::cerr << "Error al cargar la música del nivel 2." << std::endl;
    }
}

void Musica::reproducir() {
    musica.setLoop(true);
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
