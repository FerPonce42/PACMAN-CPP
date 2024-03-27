
#ifndef MUSICA_H
#define MUSICA_H

#include <SFML/Audio.hpp>

class Musica {
public:
    Musica(); 

    void cargarMusica();
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