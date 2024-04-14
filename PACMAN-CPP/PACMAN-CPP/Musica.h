#pragma once
#ifndef MUSICA_H
#define MUSICA_H

#include <SFML/Audio.hpp>

class Musica {
public:
    Musica();

    void cargarMusicaMenu();
    void cargarMusicaNivel1();
    void cargarMusicaNivel2();
    void cargarMusicaNivel3(); 
    void reproducir();
    void detener();
    void pausar();
    void reanudar();
    void setVolume(float volume);
    void setLoop(bool loop);

private:
    sf::Music musica;
};

#endif 
