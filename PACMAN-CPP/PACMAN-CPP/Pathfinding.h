#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <map>

class Pathfinding {
public:
    // Constructor de la clase Pathfinding
    Pathfinding(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);

    // M�todo para encontrar el camino desde una posici�n inicial a una posici�n objetivo
    std::vector<sf::Vector2f> encontrarCamino(sf::Vector2f inicio, sf::Vector2f objetivo);

private:
    int** mapa;
    int anchoMapa;
    int altoMapa;
    float anchoCelda;
    float altoCelda;
    float posXInicio;
    float posYInicio;

    // M�todo para convertir una posici�n en coordenadas de celda
    std::pair<int, int> posicionACelda(sf::Vector2f posicion);

    // M�todo para convertir una celda en posici�n
    sf::Vector2f celdaAPosicion(int fila, int columna);

    // M�todo para obtener los vecinos de una celda
    std::vector<std::pair<int, int>> obtenerVecinos(int fila, int columna);

    // M�todo para calcular la heur�stica (distancia de Manhattan)
    float heuristica(std::pair<int, int> a, std::pair<int, int> b);
};
