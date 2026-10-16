#include "pacman/Game.hpp"


void Game::run() {
    window.create(sf::VideoMode(800, 600), "Pac-Man");

    while (window.isOpen()) {

        processEvents();
        render();
        update();

    }

}


void Game::processEvents() {

    sf::Event event;

    while (window.pollEvent(event))
    {
        
        if (event.type == sf::Event::Closed) {
            window.close();
        }

    }
    
}


void Game::render() {

    window.clear(sf::Color::Black);

    sf::CircleShape player(20.f);
    player.setFillColor(sf::Color::Yellow);
    player.setPosition(10.f, 10.f);
    window.draw(player);

    window.display();

}


void Game::update() {



}