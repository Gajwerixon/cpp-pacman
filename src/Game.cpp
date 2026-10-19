#include "pacman/Game.hpp"

Game::Game() {
    player.setStartPosition(maze.getPacmanStart());
};


void Game::run() {
    window.create(sf::VideoMode(672, 864), "Pac-Man");

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
        
        player.handleEvents(event);

    }
    
}


void Game::render() {

    window.clear(sf::Color::Black);

    maze.render(window);
    player.render(window);

    window.display();

}


void Game::update() {

    float deltaTime = clock.restart().asSeconds();

    player.update(deltaTime);

}