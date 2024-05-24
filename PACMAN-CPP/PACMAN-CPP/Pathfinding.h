#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <map>

class Pathfinding {
public:
    // Constructor de la clase Pathfinding
    Pathfinding(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio);

    // Método para encontrar el camino desde una posición inicial a una posición objetivo
    std::vector<sf::Vector2f> encontrarCamino(sf::Vector2f inicio, sf::Vector2f objetivo);

private:
    int** mapa;
    int anchoMapa;
    int altoMapa;
    float anchoCelda;
    float altoCelda;
    float posXInicio;
    float posYInicio;

    // Método para convertir una posición en coordenadas de celda
    std::pair<int, int> posicionACelda(sf::Vector2f posicion);

    // Método para convertir una celda en posición
    sf::Vector2f celdaAPosicion(int fila, int columna);

    // Método para obtener los vecinos de una celda
    std::vector<std::pair<int, int>> obtenerVecinos(int fila, int columna);

    // Método para calcular la heurística (distancia de Manhattan)
    float heuristica(std::pair<int, int> a, std::pair<int, int> b);
};
