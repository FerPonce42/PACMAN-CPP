#include "Jugador.h" 
#include <iostream> 

// Constructor de la clase Jugador
Jugador::Jugador(float x, float y, float velocidad) : velocidad(velocidad) {
    // Carga la textura del jugador desde un archivo
    if (!textura.loadFromFile("Nivel1/derecha.png")) {
        std::cerr << "Error al cargar la textura del jugador." << std::endl;
    }

    // Configura el sprite del jugador con la textura cargada
    sprite.setTexture(textura);
    sprite.setPosition(900, 540); // Establece la posici�n inicial del jugador
    sprite.setScale(0.8f, 0.8f); // Escala el tama�o del jugador
}

// M�todo para verificar si una posici�n propuesta es v�lida en el mapa
bool Jugador::posicionValida(sf::Vector2f nuevaPosicion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
    float jugadorAncho = sprite.getGlobalBounds().width; // Ancho del sprite del jugador
    float jugadorAlto = sprite.getGlobalBounds().height; // Alto del sprite del jugador

    std::vector<sf::Vector2f> puntos; // Vector para almacenar puntos de colisi�n

    // Esquinas del jugador
    puntos.push_back(nuevaPosicion);
    puntos.push_back({ nuevaPosicion.x + jugadorAncho, nuevaPosicion.y });
    puntos.push_back({ nuevaPosicion.x, nuevaPosicion.y + jugadorAlto });
    puntos.push_back({ nuevaPosicion.x + jugadorAncho, nuevaPosicion.y + jugadorAlto });

    // Puntos intermedios en los lados del jugador
    for (float x = nuevaPosicion.x + 1; x < nuevaPosicion.x + jugadorAncho; x += anchoCelda / 2) {
        puntos.push_back({ x, nuevaPosicion.y });
        puntos.push_back({ x, nuevaPosicion.y + jugadorAlto });
    }
    for (float y = nuevaPosicion.y + 1; y < nuevaPosicion.y + jugadorAlto; y += altoCelda / 2) {
        puntos.push_back({ nuevaPosicion.x, y });
        puntos.push_back({ nuevaPosicion.x + jugadorAncho, y });
    }

    // Verificar cada punto en el mapa
    for (auto& punto : puntos) {
        int columna = static_cast<int>((punto.x - posXInicio) / anchoCelda); // Columna en el mapa
        int fila = static_cast<int>((punto.y - posYInicio) / altoCelda); // Fila en el mapa

        // Verifica si el punto est� fuera de los l�mites del mapa o colisiona con un obst�culo
        if (fila < 0 || fila >= altoMapa || columna < 0 || columna >= anchoMapa || mapa[fila][columna] != 0) {
            return false; // La posici�n no es v�lida
        }
    }

    return true; // La posici�n es v�lida
}

// M�todo para mover al jugador en una direcci�n dada
void Jugador::mover(sf::Vector2f direccion, int** mapa, int anchoMapa, int altoMapa, float anchoCelda, float altoCelda, float posXInicio, float posYInicio) {
    sf::Vector2f nuevaPosicion = sprite.getPosition() + direccion * velocidad; // Calcula la nueva posici�n del jugador

    // Verifica si la nueva posici�n es v�lida en el mapa
    if (posicionValida(nuevaPosicion, mapa, anchoMapa, altoMapa, anchoCelda, altoCelda, posXInicio, posYInicio)) {
        sprite.setPosition(nuevaPosicion); // Actualiza la posici�n del jugador
    }
}

// M�todo para dibujar al jugador en una ventana dada
void Jugador::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(sprite); // Dibuja el sprite del jugador en la ventana
}

// M�todo para cambiar la textura del jugador
void Jugador::cambiarTextura(const std::string& archivoTextura) {
    // Carga una nueva textura desde un archivo
    if (!textura.loadFromFile("Nivel1/" + archivoTextura)) {
        std::cerr << "Error al cargar la nueva textura del jugador." << std::endl;
    }

    // Establece la nueva textura en el sprite del jugador
    sprite.setTexture(textura);
}

// M�todo para establecer la direcci�n del jugador
void Jugador::setDireccion(sf::Vector2f nuevaDireccion) {
    direccion = nuevaDireccion; // Actualiza la direcci�n del jugador
}

// M�todo para obtener la posici�n del jugador
sf::Vector2f Jugador::getPosicion() const {
    return sprite.getPosition(); // Devuelve la posici�n actual del jugador
}

// M�todo para obtener la direcci�n del jugador
sf::Vector2f Jugador::getDireccion() const {
    return direccion; // Devuelve la direcci�n actual del jugador
}