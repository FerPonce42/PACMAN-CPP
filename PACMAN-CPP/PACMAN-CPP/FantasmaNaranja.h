#pragma once
#include "fantasmaPadre.h"

class FantasmaNaranja : public FantasmaPadre {
public:
    FantasmaNaranja(float x, float y, float velocidad);

    // Implementaci�n de m�todo de movimiento espec�fico para FantasmaNaranja
    void mover(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio, sf::Vector2f posicionJugador) override;
};
