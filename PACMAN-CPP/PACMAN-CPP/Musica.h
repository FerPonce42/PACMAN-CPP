#pragma once
#ifndef MUSICA_H
#define MUSICA_H

#include <SFML/Audio.hpp>

class Musica {
public:
    Musica();

    void cargarMusicaMenu();
    void cargarMusicaNivel1();
    void cargarMusicaNivel2(); // Nuevo método para cargar la música del nivel 2
    void reproducir();
    void detener();
    void pausar();
    void reanudar();
    void setVolume(float volume);
    void setLoop(bool loop);

private:
    sf::Music musica;
};

#endif // MUSICA_H
