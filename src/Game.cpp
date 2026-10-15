#include "pacman/Game.hpp"

void Game::run() {
    window.create(sf::VideoMode(800, 600), "Pac-Man");

    while (window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }

    }

}