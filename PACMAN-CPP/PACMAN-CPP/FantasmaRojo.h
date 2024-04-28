#pragma once
#include "fantasmaPadre.h"

class FantasmaRojo : public FantasmaPadre {
public:
    FantasmaRojo(float x, float y, float velocidad);

    // Implementación de método de movimiento específico para FantasmaRojo
    void mover(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio, sf::Vector2f posicionJugador) override;
};
