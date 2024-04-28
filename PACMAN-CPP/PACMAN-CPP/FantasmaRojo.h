#pragma once
#include "fantasmaPadre.h"

class FantasmaRojo : public FantasmaPadre {
public:
    FantasmaRojo(float x, float y, float velocidad);

    // Implementaci�n de m�todo de movimiento espec�fico para FantasmaRojo
    void mover(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio, sf::Vector2f posicionJugador) override;
};
