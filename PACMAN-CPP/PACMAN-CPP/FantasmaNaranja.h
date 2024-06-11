#pragma once
#include "FantasmaRojo.h"

class FantasmaNaranja : public FantasmaRojo {
public:
    FantasmaNaranja(float x, float y, float velocidad);

    void setPosicionInicial() override;
    void moverAI(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio, sf::Vector2f playerPosition, bool powerActive) override;
    void setDireccion(sf::Vector2f nuevaDireccion) override;
};
