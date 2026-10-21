#include "pacman/Game.hpp"

Game::Game() {
    player.setStartPosition(
        maze.getPacmanStart(), 
        maze.calculateScreenPosition(maze.getPacmanStart())
    );
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

    updatePlayer(deltaTime);

}


void Game::updatePlayer(float deltaTime) {

    player.update(deltaTime);

    // Get player current screenPosition
    sf::Vector2f screenPostion = player.getScreenPosition();

    // Calculate current player tilePosition
    sf::Vector2i tilePosition = maze.calculateTilePosition(screenPostion);

    // If the current tile position is diffrent => Set the new player tile position
    if (tilePosition != player.getTilePosition()) {
        player.setTilePosition(tilePosition);
    }

}