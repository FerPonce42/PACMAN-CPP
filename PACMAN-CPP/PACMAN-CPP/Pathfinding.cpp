#include "Pathfinding.h"
#include <cmath>
#include <set>

Pathfinding::Pathfinding(int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio)
    : mapa(mapa), anchoMapa(anchoMapa), altoMapa(altoMapa), anchoCelda(anchoCelda), altoCelda(altoCelda), posXInicio(posXInicio), posYInicio(posYInicio) {}

std::vector<sf::Vector2f> Pathfinding::encontrarCamino(sf::Vector2f inicio, sf::Vector2f objetivo) {
    auto inicioCelda = posicionACelda(inicio);
    auto objetivoCelda = posicionACelda(objetivo);

    std::set<std::pair<int, int>> cerrados;
    std::priority_queue<std::pair<float, std::pair<int, int>>, std::vector<std::pair<float, std::pair<int, int>>>, std::greater<>> abiertos;
    std::map<std::pair<int, int>, std::pair<int, int>> cameFrom;
    std::map<std::pair<int, int>, float> gScore;

    abiertos.push({ 0, inicioCelda });
    gScore[inicioCelda] = 0;

    while (!abiertos.empty()) {
        auto current = abiertos.top().second;
        abiertos.pop();

        if (current == objetivoCelda) {
            std::vector<sf::Vector2f> path;
            while (current != inicioCelda) {
                path.push_back(celdaAPosicion(current.first, current.second));
                current = cameFrom[current];
            }
            path.push_back(celdaAPosicion(inicioCelda.first, inicioCelda.second));
            std::reverse(path.begin(), path.end());
            return path;
        }

        cerrados.insert(current);
        for (auto& vecino : obtenerVecinos(current.first, current.second)) {
            if (cerrados.find(vecino) != cerrados.end()) continue;

            float tentative_gScore = gScore[current] + heuristica(current, vecino);

            if (gScore.find(vecino) == gScore.end() || tentative_gScore < gScore[vecino]) {
                cameFrom[vecino] = current;
                gScore[vecino] = tentative_gScore;
                float fScore = tentative_gScore + heuristica(vecino, objetivoCelda);
                abiertos.push({ fScore, vecino });
            }
        }
    }

    return {}; // No se encontró un camino
}

std::pair<int, int> Pathfinding::posicionACelda(sf::Vector2f posicion) {
    int columna = static_cast<int>((posicion.x - posXInicio) / anchoCelda);
    int fila = static_cast<int>((posicion.y - posYInicio) / altoCelda);
    return { fila, columna };
}

sf::Vector2f Pathfinding::celdaAPosicion(int fila, int columna) {
    float x = posXInicio + columna * anchoCelda;
    float y = posYInicio + fila * altoCelda;
    return { x, y };
}

std::vector<std::pair<int, int>> Pathfinding::obtenerVecinos(int fila, int columna) {
    std::vector<std::pair<int, int>> vecinos;
    if (fila > 0 && mapa[fila - 1][columna] == 0) vecinos.push_back({ fila - 1, columna });
    if (fila < altoMapa - 1 && mapa[fila + 1][columna] == 0) vecinos.push_back({ fila + 1, columna });
    if (columna > 0 && mapa[fila][columna - 1] == 0) vecinos.push_back({ fila, columna - 1 });
    if (columna < anchoMapa - 1 && mapa[fila][columna + 1] == 0) vecinos.push_back({ fila, columna + 1 });
    return vecinos;
}

float Pathfinding::heuristica(std::pair<int, int> a, std::pair<int, int> b) {
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}
